
#include <quick/crash.h>
#include <quick/mem.h>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

t_ptr base_memallocator::alloc(t_bytsize sz)
{
  if(sz < 0) quick_crash(errcode::bad_param, "SIZE_LESS_ZERO: sz=%lld", (t_llong)sz);
  if(sz <= 0) return nullptr;
  
  t_bytsize *p = nullptr;
  try{
  
    if(nullptr == (p = (t_bytsize *)::operator new((size_t)sz + sizeof(*p))))
      return nullptr;
  
  }catch(...)
  {
    quick_crash(errcode::bad_alloc, "EXCEPTION_ON_MEM_NEW");
  }
  
  *p = sz;
  
  _stat.alloc_count++;
  _stat.alloc_size += sz + sizeof(*p);
  
  if(_stat.alloc_count < 0 || _stat.alloc_size < 0)
    quick_crash(errcode::impossible, "MEMSTAT_OFF_SIZE");
  return ++p;
}

void base_memallocator::release(t_ptr ptr)
{
  if(nullptr == ptr) return;
  
  t_bytsize *p = (t_bytsize *)ptr - 1;
  if(*p <= 0) quick_crash(errcode::bad_param, "INVALID_BLOCK_OR_BROKEN");
  
  _stat.del_count++;
  _stat.del_size += *p + sizeof(*p);
  *p = 0;
  
  if(_stat.del_count < 0 || _stat.del_size < 0)
    return quick_crash(errcode::impossible, "MEMSTAT_OFF_SIZE");
  
  if(_stat.block_count() < 0 || _stat.total_size() < 0)
    return quick_crash(errcode::bad_logic, "MEMSTAT_ERROR");
  
  try{
  
    ::operator delete(p);
  
  }catch(...)
  {
    quick_crash(errcode::bad_delete, "EXCEPTION_ON_MEM_DELETE");
  }
  return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
}
// END
