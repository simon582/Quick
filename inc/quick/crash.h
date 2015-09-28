
#ifndef _QK_CRASH_H_
#define _QK_CRASH_H_

#include <quick/types.h>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

class srcinfo
{
public:
  t_constr srouce = nullptr;
  t_constr func = nullptr;
  int line = -1;
public:
  inline srcinfo(t_constr src, t_constr fun, int ln): srouce(src), func(fun), line(ln){}
};

#define quick_srcinfo quick::srcinfo(__FILE__,__FUNCTION__,__LINE__)

class crashor
{
public:
  static void abort(srcinfo info, int code = errcode::crashed, t_constr msg = nullptr, ...);
  static void assert_fail(srcinfo info, t_constr expr);
};

#define quick_crash(...) quick::crashor::abort(quick_srcinfo, __VA_ARGS__)

#ifdef _ASSERT_
#define quick_assert(_expr_) \
  do{ if(!(_expr_)) quick::crashor::assert_fail(quick_srcinfo, #_expr_); }while(0)
#else
#define quick_assert(_expr_)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif
// END
