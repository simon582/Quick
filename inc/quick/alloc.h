
#ifndef _QK_ALLOC_H_
#define _QK_ALLOC_H_

#include <quick/crash.h>
#include <quick/mem.h>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

class constructor
{
public:
  template<typename _t>
  inline static _t * construct(_t *ptr)
  { return nullptr == ptr ? ptr : new (ptr) _t(); }
  template<typename _t>
  inline static _t * construct(_t *begin, _t *end)
  { for(_t *p = begin; p < end; new (p++) _t()){} return begin; }
  template<typename _t>
  inline static _t * construct_copy(_t *ptr, const _t &src)
  { return nullptr == ptr ? ptr : new (ptr) _t(src); }
  template<typename _t>
  inline static _t * construct_copy(_t *begin, _t *end, const _t *src)
  { for(_t *p = begin; p < end; new (p++) _t(*(src++))){} return begin; }
  template<typename _t>
  inline static _t * construct_move(_t *ptr, _t &src)
  {
    if(nullptr == ptr) return nullptr;
    ::memcpy(ptr, &src, sizeof(_t)); construct(&src);
    return ptr;
  }
  template<typename _t>
  inline static void * destruct(_t *ptr)
  { if(nullptr != ptr) ptr->~_t(); return ptr; }
  template<typename _t>
  inline static void * destruct(_t *begin, _t *end)
  { for(_t *p = begin; p < end; (p++)->~_t()){} return begin; }
};

template<typename _a = default_memallocator>
class allocator
{
public:
  typedef _a memory_allocator;
  typedef allocator<memory_allocator> self;
protected:
  memory_allocator _ma;
public:
  allocator() = default;
  ~allocator() = default;
private:
  allocator(const self &) = delete;
  self & operator=(const self &) = delete;
public:
  inline const memory_allocator & ma() const  { return _ma; }
  inline memory_allocator & ma()              { return _ma; }
  inline memstat stat() const                 { return _ma.stat(); }
public:
  template<typename _t>
  inline _t * alloc()
  { return constructor::construct((_t *)_ma.alloc(sizeof(_t))); }
  template<typename _t>
  inline _t * alloc(int n)
  { _t *p = (_t *)_ma.alloc(sizeof(_t)*n); return constructor::construct(p, p+n); }
  template<typename _t>
  inline _t * realloc(_t *old, int old_num, int new_num)
  {
    if(new_num <= old_num) return old;
    _t *p = (_t *)_ma.alloc(sizeof(_t)*new_num);
    if(nullptr == p) return nullptr;
    ::memmove(p, old, sizeof(_t)*old_num);
    _ma.release(old);
    constructor::construct(p + old_num, p + new_num);
    return p;
  }
  template<typename _t>
  inline void release(_t *ptr)
  { return _ma.release(constructor::destruct(ptr)); }
  template<typename _t>
  inline void release(_t *ptr, int n)
  { return _ma.release(constructor::destruct(ptr, ptr+n)); }
public:
  static self dft;
};

template<typename _a>
allocator<_a> allocator<_a>::dft;

typedef allocator<default_memallocator> default_allocator;

////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif
// END
