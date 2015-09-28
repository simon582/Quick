
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

#include <quick/time.h>
#include <quick/file.h>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

void file::open(t_constr filename, int mode)
{
  int m = 0;
  m |= (openmode::create & mode) ? O_CREAT : 0;
  m |= (openmode::append & mode) ? O_APPEND : 0;
  m |= (openmode::replace & mode) ? O_TRUNC : 0;
  m |= (openmode::read & mode) ? (openmode::write & mode ? O_RDWR : O_RDONLY)
    : (openmode::write & mode ? O_WRONLY : 0);
    
  close();
  if(0 > (_fd = ::open(filename, m, S_IREAD | S_IWRITE)))
    return quick_crash(errno, "BAD_FILE_OPEN: %s", ::strerror(errno));
  return;
}

void file::close()
{
  if(!isopen()) return;
  
  if(0 != ::close(_fd)) return quick_crash(errno, "BAD_FILE_CLOSE: %s", ::strerror(errno));
  _fd = nulls::hdl;
  return;
}

static constexpr t_bytsize _file_rdwr_persize = 256 * 1024 * 1024;
void file::read(t_ptr buf, t_bytsize sz)
{
  while(sz > 0)
  {
    t_bytsize n = (sz > _file_rdwr_persize) ? _file_rdwr_persize : sz;
    if(n != (t_bytsize)::read(_fd, buf, (size_t)n))
      return quick_crash(errno, "BAD_FILE_READ: %s", ::strerror(errno));
    buf = (t_byt *)buf + n;
    sz -= n;
  }
  return;
}

void file::write(t_conptr buf, t_bytsize sz)
{
  while(sz > 0)
  {
    t_bytsize n = (sz > _file_rdwr_persize) ? _file_rdwr_persize : sz;
    if(n != (t_bytsize)::write(_fd, buf, (size_t)n))
      return quick_crash(errno, "BAD_FILE_WRITE: %s", ::strerror(errno));
    buf = (const t_byt *)buf + n;
    sz -= n;
  }
  return;
}

t_offset file::seek_begin(t_offset pos)
{
  t_offset ret = nulls::offset;
  if(0 > (ret = ::lseek(_fd, (off_t)pos, SEEK_SET)))
    quick_crash(errno, "BAD_FILE_SEEK: %s", ::strerror(errno));
  return ret;
}

t_offset file::seek_end(t_offset pos)
{
  t_offset ret = nulls::offset;
  if(0 > (ret = ::lseek(_fd, (off_t)pos, SEEK_END)))
    quick_crash(errno, "BAD_FILE_SEEK: %s", ::strerror(errno));
  return ret;
}

t_offset file::seek_curr(t_offset pos)
{
  t_offset ret = nulls::offset;
  if(0 > (ret = ::lseek(_fd, (off_t)pos, SEEK_CUR)))
    quick_crash(errno, "BAD_FILE_SEEK: %s", ::strerror(errno));
  return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

t_bytsize file::fsize(t_constr filename)
{
  struct stat st;
  if(0 != ::stat(filename, &st)) return nulls::bytsize;
  return (t_bytsize)st.st_size;
}

void file::fload(t_constr filename, hugestack<t_byt> &dest)
{
  return fload(filename, *((hugestack<char> *)&dest), nullptr);
}

void file::fload(t_constr filename, hugestack<char> &dest, t_constr end_symbol)
{
  t_bytsize sz = fsize(filename);
  if(sz < 0)
    return quick_crash(errcode::bad_param, "FILE_NOT_EXIST: file=%s", filename);
  
  int n = 0;
  if(nullptr != end_symbol) n = strlen(end_symbol) + 1;
  dest.create(sz + n);
  
  file input;
  input.open(filename, file::openmode::read);
  input.read(dest.buffer(), sz);
  input.close();
  
  ::memcpy(dest.buffer() + sz, end_symbol, n);
  return;
}

void file::fload(t_constr filename, array<str_lnr_map> &maps)
{
  file_line_reader input;
  input.load(filename);
  
  maps.clear();
  for(int i = 0; i < input.length(); ++i)
  {
    char *p = (char *)::strchr(input[i], '#');
    if(nullptr != p) *p = nulls::chr;
    
    if(nulls::chr == *(input[i])) continue;
    
    str_lnr_map *map = maps.append();
    map->puts(input[i]);
    
    if(map->length() <= 0) maps.remove_back();
  }
  return;
}

void file::fload(t_constr filename, str_lnr_map &map)
{
  file_line_reader input;
  input.load(filename);

  map.clear();
  for(int i = 0; i < input.length(); ++i)
  {
    char *p = (char *)::strchr(input[i], '#');
    if(nullptr != p) *p = nulls::chr;
    
    if(nulls::chr == *(input[i])) continue;
    
    map.puts(input[i], false);
  }
  return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void file_line_reader::load(t_constr filename, t_constr split, bool del_last_empty_lns)
{
  t_tmus begin = timeus::current();
  file::fload(filename, _data);
  t_tmus end = timeus::current();
  _size_per_sec = _data.bytsize() * 1000000 / (end - begin + 1); 
  
  index(split);
  
  if(del_last_empty_lns) delete_last_empty_lines();
  
  return;
}

void file_line_reader::loadstr(t_constr str, t_constr split, bool del_last_empty_lns)
{
  size_t n = ::strlen(str) + 1;
  _data.create(n);
  ::memcpy(_data.buffer(), str, n);
  
  index(split);
  
  if(del_last_empty_lns) delete_last_empty_lines();
  
  return;
}

void file_line_reader::release()
{
  _data.release();
  _idx.release();
  return;
}

void file_line_reader::index(t_constr split)
{
  _idx.clear();
  
  int n = ::strlen(split);
  
  t_str p = _data.buffer();
  while(true)
  {
    _idx.append(p);
    
    if(nullptr == (p = ::strstr(p, split)))
      break;
      
    *p = nulls::chr;
    p += n;
  }
  return;
}

void file_line_reader::delete_last_empty_lines()
{
  while(_idx.length() > 0 && nulls::chr == _idx.atback(0)[0])
    _idx.remove_back();
  return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
}
// END
