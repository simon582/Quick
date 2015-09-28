
#include <quick/strs.h>
#include <quick/file.h>
#include <quick/kvmap.h>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

void str_lnr_map::put(t_constr key, t_constr val)
{
  pair *p = (pair *)get(key);
  if(nullptr == p){ p = _pairs.append(); p->key = key; }
  p->val = val;
  return;
}

const str_lnr_map::pair * str_lnr_map::get(t_constr key) const
{
  int id = getid(key);
  return id >= 0 ? &_pairs[id] : nullptr;
}

int str_lnr_map::getid(t_constr key) const
{
  for(int i = 0; i < _pairs.length(); ++i)
    if(0 == ::strcmp(_pairs[i].key, key))
      return i;
  return -1;
}

t_constr str_lnr_map::getval(t_constr key, t_constr dft) const
{
  const pair *p = get(key);
  if(nullptr == p) return dft;
  return p->val;
}

int str_lnr_map::getvalint(t_constr key, int dft) const
{
  t_constr val = getval(key, nullptr);
  if(nullptr == val) return dft;
  return strs::toint(val, dft);
}

inline static bool _issplit(char c)
{
  return 0 < c && c <= 32;
}

void str_lnr_map::puts(t_constr argvs, bool clear)
{
  if(clear) this->clear();
  while(true)
  {
    // "  key  =  val  "
    //  ^:argvs
  
    while(_issplit(*argvs)) ++argvs;
    if(nulls::chr == *argvs) return;
    
    // "  key  =  val  "
    //    ^:argvs
    
    t_constr begin = argvs;
    while(nulls::chr != *argvs && !_issplit(*argvs)) ++argvs;
    if(nulls::chr == *argvs) return put_argv(begin);
    cstring s(begin, argvs);
    if(nullptr != ::strchr(s, '=')){ put_argv(s); continue; }
    
    // "  key  =  val  "
    //        ^:argvs
    //    [ ]:s
    
    while(_issplit(*argvs)) ++argvs;
    if(nulls::chr == *argvs) return put_argv(s);
    if('=' != *argvs){ put_argv(s); continue; }
    
    // "  key  =  val  "
    //         ^:argvs
    //    [ ]:s
    
    ++argvs;
    while(_issplit(*argvs)) ++argvs;
    if(nulls::chr == *argvs) return put_argv(s);
    
    // "  key  =  val  "
    //            ^:argvs
    //    [ ]:s
    
    pair pa;
    pa.key = s;
    begin = argvs;
    while(nulls::chr != *argvs && !_issplit(*argvs)) ++argvs;
    pa.val.copy(begin, argvs);
    put(pa.key, pa.val);
    if(nulls::chr == *argvs) break;
    
    // "  key  =  val  "
    //               ^:argvs
    //    [ ]:key [ ]:val
    
    continue;
  }
  return;
}

void str_lnr_map::puts_str(t_constr argvs, t_constr split)
{
  file_line_reader argv;
  argv.loadstr(argvs, split);
  
  for(int i = 0; i < argv.length(); ++i)
    put_argv(argv[i]);
  return;
}

void str_lnr_map::put_argv(t_constr argv)
{
  if(nullptr == argv || nulls::chr == *argv)
    return;
  
  t_constr p = ::strchr(argv, '=');
  if(nullptr == p) return put(argv, nullptr);
  
  cstring key(argv, p);
  if(key.isempty())
    return quick_crash(errcode::bad_param, "KEY_IS_NULL: argv=%s", argv);
  
  return put(key, ++p);
}

void str_lnr_map::look() const
{
  fprintf(stdout, "===> str_lnr_map: length=%d\n", length());
  for(int i = 0; i < _pairs.length(); ++i)
    fprintf(stdout, " ===> pair: id=%d key=%s val=%s\n",
      i, configures::strfmt(_pairs[i].key.buffer()), configures::strfmt(_pairs[i].val.buffer()));
  return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
}
// END
