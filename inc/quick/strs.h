
#ifndef _QK_STRS_H_
#define _QK_STRS_H_

#include <quick/types.h>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

class strs
{
public:
  _crash_ static int toint(t_constr str);
  static int toint(t_constr str, int err);
  static int toint(t_constr str, bool &succ);
  _crash_ static t_i64 toi64(t_constr str);
  static t_i64 toi64(t_constr str, int err);
  static t_i64 toi64(t_constr str, bool &succ);
  _crash_ static double todouble(t_constr str);
  static double todouble(t_constr str, double err);
  static double todouble(t_constr str, bool &succ);
  static t_constr numbers(t_str str);
  static t_constr bytes_fmt(t_str buf16, t_bytsize sz);
  _nosafe_ static t_constr bytes_fmt(t_bytsize sz);
  static t_constr timespan_fmt(t_str buf16, t_tmspanus usec);
  _nosafe_ static t_constr timespan_fmt(t_tmspanus usec);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif
// END
