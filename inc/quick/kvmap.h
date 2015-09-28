
#ifndef _QK_KVMAP_H_
#define _QK_KVMAP_H_

#include <quick/string.h>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename _k, typename _v>
class kvpair
{
public:
  _k key;
  _v val;
};

template<typename _k, typename _v>
class lnr_map
{
public:
  typedef _k key;
  typedef _v value;
  typedef kvpair<key, value> pair;
  typedef lnr_map<key, value> self;
protected:
  array<pair> _pairs;
public:
  inline int length() const                   { return _pairs.length(); }
  inline const pair & at(int i) const         { return _pairs[i]; }
  inline const pair & operator[](int i) const { return _pairs[i]; }
public:
  inline void clear()
  { return _pairs.clear(); }
  inline void put(const key &k, const value &v)
  {
    pair *p = (pair *)get(k);
    if(nullptr == p){ p = _pairs.append(); p->key = k; }
    p->val = v;
    return;
  }
  inline const pair * get(const key &k) const
  { int id = getid(k); return id >= 0 ? &_pairs[id] : nullptr; }
  inline int getid(const key &k) const
  {
    for(int i = 0; i < _pairs.length(); ++i)
      if(k == _pairs[i].key)
        return i;
    return -1;
  }
  _crash_ const value & getval(const key &k) const
  {
    const pair *p = get(k);
    if(nullptr == p) quick_crash(errcode::notfound);
    return p->val;
  }
  const value & getval(const key &k, const value &dft) const
  {
    const pair *p = get(k);
    if(nullptr == p) return dft;
    return p->val;
  }
};

class str_lnr_map: public lnr_map<cstring, cstring>
{
public:
  typedef kvpair<cstring, cstring> pair;
  typedef lnr_map<cstring, cstring> father;
public:
  using father::lnr_map;
public:
  using father::put;
  using father::get;
  using father::getid;
  using father::getval;
  void put(t_constr key, t_constr val);
  const pair * get(t_constr key) const;
  int getid(t_constr key) const;
  t_constr getval(t_constr key, t_constr dft = nullptr) const;
  int getvalint(t_constr key, int dft) const;
public:
  void puts(t_constr argvs, bool clear = false);
  void puts_str(t_constr argvs, t_constr split);
  void look() const;
protected:
  void put_argv(t_constr argv);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif
// END
