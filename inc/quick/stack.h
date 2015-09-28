
#ifndef _QK_STACK_H_
#define _QK_STACK_H_

#include <quick/alloc.h>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename _t, typename _n = int>
class stack
{
public:
  typedef _t element;
  typedef _n number;
  typedef stack<element, number> self;
protected:
  element *_buf = nullptr;
  number _size = 0;
public:
  inline stack() = default;
  inline ~stack(){ release(); }
  inline explicit stack(number n){ create(n); }
private:
  stack(const self &) = delete;
  self & operator=(const self &) = delete;
public:
  inline const element * buffer() const             { return _buf; }
  inline const element * begin() const              { return _buf; }
  inline const element * end() const                { return _buf + _size; }
  inline const element & at(number i) const         { return _buf[i]; }
  inline const element & atback(number i) const     { return _buf[_size-1-i]; }
  inline element * buffer()                         { return _buf; }
  inline element * begin()                          { return _buf; }
  inline element * end()                            { return _buf + _size; }
  inline element & at(number i)                     { return _buf[i]; }
  inline element & atback(number i)                 { return _buf[_size-1-i]; }
  inline number length() const                      { return _size; }
  inline t_bytsize bytsize() const                  { return _size * sizeof(element); }
  inline bool isnull() const                        { return nullptr == _buf; }
public:
  inline operator const element *() const           { return _buf; }
  inline operator element *()                       { return _buf; }
  inline const element & operator[](number i) const { return _buf[i]; }
  inline element & operator[](number i)             { return _buf[i]; }
public:
  inline void create(number n)
  {
    if(n == _size) return;
    release();
    _buf = default_allocator::dft.alloc<element>(n);
    _size = n; return;
  }
  inline void resize(number n)
  {
    if(n <= _size) return;
    _buf = default_allocator::dft.realloc(_buf, _size, n);
    _size = n; return;
  }
  inline void release()
  {
    default_allocator::dft.release(_buf, _size);
    _buf = nullptr; _size = 0; return;
  }
  inline void setall(const element &elem)
  {
    for(int i = 0; i < _size; _buf[i++] = elem){} return;
  }
};

template<typename _t>
class hugestack: public stack<_t, t_i64>
{
public:
  using stack<_t, t_i64>::stack;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif
// END
