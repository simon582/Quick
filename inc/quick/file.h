
#ifndef _QK_FILE_H_
#define _QK_FILE_H_

#include <quick/kvmap.h>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

class file
{
public:
  class openmode
  {
  public:
    enum _mode
    {
      create        = 0x01,
      append        = 0x02,
      replace       = 0x04,
      read          = 0x08,
      write         = 0x10,
      always_create = create | replace,
      append_create = create | append,
      readwrite     = read | write      
    };
  };

protected:
  t_hdl _fd = nulls::hdl;
public:
  inline file() = default;
  inline ~file(){ close(); }
private:
  file(const file &) = delete;
  file & operator=(const file &) = delete;
public:
  inline bool isopen() const    { return _fd >= 0; }
  inline int fd() const         { return _fd; }
  inline t_offset tell() const   { return ((file *)this)->seek_curr(0); }
public:
  void open(t_constr filename, int mode);
  void close();
  void read(t_ptr buf, t_bytsize sz);
  void write(t_conptr buf, t_bytsize sz);
  t_offset seek_begin(t_offset pos);
  t_offset seek_end(t_offset pos);
  t_offset seek_curr(t_offset pos);
  
public:
  static t_bytsize fsize(t_constr filename);
  static void fload(t_constr filename, hugestack<t_byt> &dest);
  static void fload(t_constr filename, hugestack<char> &dest, t_constr end_symbol = "");
  static void fload(t_constr filename, array<str_lnr_map> &maps);
  static void fload(t_constr filename, str_lnr_map &map);
};

typedef file::openmode fomode;

////////////////////////////////////////////////////////////////////////////////////////////////////

class file_line_reader
{
protected:
  hugestack<char> _data;
  array<t_str> _idx;
  t_bytsize _size_per_sec = 0;
public:
  file_line_reader() = default;
  ~file_line_reader() = default;
private:
  file_line_reader(const file_line_reader &);
  file_line_reader & operator=(const file_line_reader &);
public:
  inline t_bytsize size_per_sec() const     { return _size_per_sec; }
  inline int length() const                 { return _idx.length(); }
  inline t_constr at(int i) const           { return _idx.at(i); }
  inline t_constr atback(int i) const       { return _idx.atback(i); }
  inline const array<t_str> & idx() const   { return _idx; }
  inline array<t_str> & idx()               { return _idx; }
public:
  inline t_constr operator[](int i) const   { return _idx[i]; }
public:
  void load(t_constr filename, t_constr split = "\n", bool del_last_empty_lns = false);
  void loadstr(t_constr str, t_constr split, bool del_last_empty_lns = false);
  void release();
protected:
  void index(t_constr split);
  void delete_last_empty_lines();
};

typedef file_line_reader str_splitor;

////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif
// END
