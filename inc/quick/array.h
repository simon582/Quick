
#ifndef _QK_ARRAY_H_
#define _QK_ARRAY_H_

#include <quick/buffs.h>
#include <quick/stack.h>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename _t>
class array: protected stack<_t>
{
public:
  typedef _t element;
  typedef array<element> self;
  typedef stack<element> father;
  typedef typename father::number number;
protected:
  number _len = 0;
protected:
  static t_bytsize _min_bytsz_prealloc;
  static t_bytsize _max_bytsz_prealloc;
public:
  inline array() = default;
  inline ~array()                                   { clear(); }
  inline array(const self &a)                       { copy(a); }
  inline self & operator=(const self &a)            { copy(a); return *this; }
  inline explicit array(number n)                   { create(n); }
  inline array(self &&a)                            { swap(a); }
public:
  inline number limit() const                       { return father::length(); }
  inline t_bytsize bytsize() const                  { return father::bytsize(); }
  inline number length() const                      { return _len; }
  inline number freelength() const                  { return limit() - _len; }
  inline const element * buffer() const             { return father::buffer(); }
  inline const element * begin() const              { return buffer(); }
  inline const element * end() const                { return buffer() + _len; }
  inline const element & at(number i) const         { return buffer()[i]; }
  inline const element & atback(number i) const     { return buffer()[_len-1-i]; }
  inline element * buffer()                         { return father::buffer(); }
  inline element * begin()                          { return buffer(); }
  inline element * end()                            { return buffer() + _len; }
  inline element & at(number i)                     { return buffer()[i]; }
  inline element & atback(number i)                 { return buffer()[_len-1-i]; }
  inline bool isnull() const                        { return father::isnull(); }
  inline bool isclear() const                       { return 0 == _len; }
  inline bool isfull() const                        { return _len == limit(); }
public:
  inline operator const element *() const           { return buffer(); }
  inline operator element *()                       { return buffer(); }
  inline const element & operator[](number i) const { return at(i); }
  inline element & operator[](number i)             { return at(i); }
public:
  inline void create(number n, bool presize = true)
  { clear(); return relength(n, presize); }
  inline void resize(number sz, bool presize = true)
  {
    if(sz <= limit()) return;
    if(presize) sz = autosize(sz);
    return father::resize(sz);
  }
  inline void release()
  { clear(); father::release(); }
  inline void relength(number n, bool presize = true)
  { if(n > limit()) resize(n, presize); _len = n; return; }
  inline void clear()
  { _len = 0; return; }
  inline void copy(const self &a)
  {
    if(this == &a) return;
    create(a.length());
    constructor::destruct(begin(), end());
    constructor::construct_copy(begin(), end(), a.begin());
    return;
  }
  inline void copy(const element *begin, const element *end)
  {
    create(end - begin);
    constructor::destruct(this->begin(), this->end());
    constructor::construct_copy(this->begin(), this->end(), begin);
    return;
  }
  inline void swap(self &a)
  { if(this != &a) buffs::swap(*this, a); return; }
public:
  inline element * append()
  { return append(_t()); }
  inline element * append(const element &elem)
  { return append(&elem, &elem + 1); }
  inline element * append(const element *begin, const element *end)
  {
    element *p = append_any(end - begin);
    constructor::destruct(p, p + (end - begin));
    return constructor::construct_copy(p, p + (end - begin), begin);
  }
  inline element * append(const element *begin, int n)
  { return append(begin, begin + n); }
  inline element * append(const self &a)
  { return append(a.begin(), a.end()); }
  // append without element copy-constructor
  inline element * append_any(number n = 1)
  {
    if(n < 0) quick_crash(errcode::bad_param, "INVALID_APPEND_COUNT: n=%d", (int)n);
    if(_len + n > limit()) resize(_len + n);
    element *p = end();
    _len += n;
    quick_assert(_len >= 0);
    return p;
  }
  inline void remove_back(number n = 1)
  {
    if(n > _len)
      quick_crash(errcode::bad_param, "CAN_NOT_REMOVE_ANYMORE: len=%d n=%d", (int)_len, (int)n);
    _len -= n;
    quick_assert(_len >= 0);
    return;
  }
protected:
  inline static t_bytsize set_min_bytsz_prealloc(t_bytsize sz)
  { return _min_bytsz_prealloc = sz; }
  inline static t_bytsize set_max_bytsz_prealloc(t_bytsize sz)
  { return _max_bytsz_prealloc = sz; }
  static number autosize(number least)
  {
    if(_min_bytsz_prealloc <= 0 || _max_bytsz_prealloc <= 0)
      quick_crash(errcode::bad_param, "PREALLOC_SIZE_INVALID");
    if(_min_bytsz_prealloc > _max_bytsz_prealloc)
      quick_crash(errcode::bad_param, "PREALLOC_SIZE_INVALID");
    const t_bytsize min = _min_bytsz_prealloc;
    const t_bytsize max = _max_bytsz_prealloc;
    const t_bytsize need = least * sizeof(_t);
    if(need <= min) return min / sizeof(_t);
    if(need >= max) return (need + max - 1) / max * max / sizeof(_t);
    t_bytsize sz = min << 1;
    while(sz < need) sz <<= 1;
    return sz / sizeof(_t);
  }
};

template<typename _t>
t_bytsize array<_t>::_min_bytsz_prealloc = configures::array_dft_min_prealloc_bytsz;

template<typename _t>
t_bytsize array<_t>::_max_bytsz_prealloc = configures::array_dft_max_prealloc_bytsz;

////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif
// END
