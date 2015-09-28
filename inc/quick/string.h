
#ifndef _QK_STRING_H_
#define _QK_STRING_H_

#include <quick/array.h>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename _t>
class string: protected array<_t>
{
public:
  typedef _t element;
  typedef array<element> father;
  typedef string<element> self;
protected:
  static constexpr _t _end = _t(0);
public:
  inline string() = default;
  inline ~string() = default;
  inline explicit string(const element *str)              { copy(str); }
  inline string(const element *begin, const element *end) { copy(begin, end); }
  inline string(const self &s): father(s){}
  inline self & operator=(const self &s)                  { copy(s); return *this; }
  inline self & operator=(const element *str)             { copy(str); return *this; }
  inline string(self &&s)                                 { swap(s); }
public:
  inline bool isnull() const                    { return father::isnull(); }
  inline bool isempty() const                   { return father::isclear() || _end == at(0); }
  inline int limit() const                      { return father::limit(); }
  inline int length() const                     { return father::length() - 1; }
  inline t_bytsize bytsize() const              { return father::bytsize(); }
  inline const element * buffer() const         { return father::buffer(); }
  inline const element & at(int i) const        { return father::at(i); }
  inline const element & atback(int i) const    { return father::atback(i); }
  inline element * buffer()                     { return father::buffer(); }
  inline element & at(int i)                    { return father::at(i); }
  inline element & atback(int i)                { return father::atback(i); }
public:
  inline operator const element *() const       { return buffer(); }
  inline explicit operator element *()          { return buffer(); }
  inline const element & operator[](int i) const{ return at(i); }
  inline element & operator[](int i)            { return at(i); }
public:
  inline element * buffer(int sz)
  { resize(sz); return buffer(); }
  inline void resize(int sz, bool presize = false)
  { return father::resize(sz, presize); }
  inline void fix()
  { return father::relength(getlength(buffer()) + 1); }
  inline void release()
  { return father::release(); }
  inline void copy(const element *str)
  { return nullptr == str ? release() : copy(str, str + getlength(str)); }
  inline void copy(const element *begin, const element *end)
  {
    if(nullptr == begin) return release();
    father::create(end - begin + 1);
    constructor::destruct(father::begin(), father::end());
    constructor::construct_copy(father::begin(), father::end() - 1, begin);
    father::atback(0) = _end;
    return;
  }
  inline void copy(const self &s)
  { return father::copy(s); }
  inline void swap(self &s)
  { return father::swap(s); }
public:
  inline static int getlength(const element *str)
  {
    if(nullptr == str) return 0;
    const element *p = str; while(_end != *p) ++p; return (int)(p - str);
  }
};

class cstring: public string<char>
{
public:
  typedef string<char> father;
public:
  using father::string;
  using father::operator=;
public:
  inline int compare(t_constr str) const
  { return ::strcmp(buffer(), str); }
  inline int compare(const self &s) const
  { return ::strcmp(buffer(), s.buffer()); }
public:
  friend bool operator==(const cstring &a, const cstring &b)    { return 0 == a.compare(b); }
  friend bool operator==(const cstring &a, t_constr b)          { return 0 == a.compare(b); }
  friend bool operator==(t_constr a, const cstring &b)          { return 0 == b.compare(a); }
  friend bool operator!=(const cstring &a, const cstring &b)    { return 0 != a.compare(b); }
  friend bool operator!=(const cstring &a, t_constr b)          { return 0 != a.compare(b); }
  friend bool operator!=(t_constr a, const cstring &b)          { return 0 != b.compare(a); }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif
// END
