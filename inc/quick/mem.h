
#ifndef _QK_MEM_H_
#define _QK_MEM_H_

#include <quick/types.h>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

class memstat
{
public:
  t_bytsize alloc_size  = 0;
  t_bytsize del_size    = 0;
  t_llong alloc_count   = 0;
  t_llong del_count     = 0;
public:
  inline t_bytsize total_size() const { return alloc_size - del_size; }
  inline t_llong block_count() const  { return alloc_count - del_count; }
};

class base_memallocator
{
protected:
  memstat _stat;
public:
  base_memallocator() = default;
  ~base_memallocator() = default;
private:
  base_memallocator(const base_memallocator &) = delete;
  base_memallocator & operator=(const base_memallocator &) = delete;
public:
  inline memstat stat() const{ return _stat; }
  _interface_ t_ptr alloc(t_bytsize sz);
  _interface_ void release(t_ptr ptr);
};

typedef base_memallocator default_memallocator;

////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif
// END
