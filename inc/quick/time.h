
#ifndef _QK_TIME_H_
#define _QK_TIME_H_

#include <quick/types.h>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

class timedate
{
public:
  int year    = 0;
  int month   = 0;
  int day     = 0;
  int hour    = 0;
  int minute  = 0;
  int second  = 0;
  int us      = 0;
};

class timeus
{
public:
  static constexpr int _uspersec = 1000000;
public:
  static t_tmus current();
  inline static t_tmsec seconds(t_tmus t){ return (t_tmsec)(t / _uspersec); }
  inline static int usec(t_tmus t){ return (int)(t % _uspersec); }
  static timedate date(t_tmus t);
};

class timesec
{
public:
  static t_tmsec current();
  static timedate date(t_tmsec t);
  static int diffdays(t_tmsec end, t_tmsec begin);
  static int diffmonths(t_tmsec end, t_tmsec begin);
};

class timespan
{
public:
  t_tmus beg  = nulls::time;
  t_tmus ed   = nulls::time;
public:
  inline timespan(){ begin(); }
public:
  inline void begin(){ beg = timeus::current(); }
  inline t_tmspanus end(){ ed = timeus::current(); return usec(); }
  inline t_tmspanus usec() const { return ed - beg; }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif
// END
