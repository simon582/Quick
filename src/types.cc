
#include <quick/types.h>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

int errcode::rela(int err)
{
  if(err <= _begin || err >= _end) return err;
  return err - _begin;
}

t_constr errcode::errstr(int err)
{
  if(0 < err && err < 128) return ::strerror(err);
  
  if(success == err) return "success";
  
  if(err < _begin || err > _end) return nullptr;
  
  switch(err)
  {
  case _begin:      return "begin-code for invalid";
  case crashed:     return "program crashed";
  case impossible:  return "that impossible but happend";
  case bad_assert:  return "bad assert";
  case bad_alloc:   return "bad memory allocate";
  case bad_delete:  return "bad memory delete";
  case bad_param:   return "bad parameter into";
  case bad_status:  return "bad status allowed";
  case bad_logic:   return "bad program logical";
  case bad_data:    return "bad data content or logical";
  case notfound:    return "not found";
  case _end:        return "end-code for invalid";
  default:          return "errcode lost string";
  }
  
  return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
}
// END
