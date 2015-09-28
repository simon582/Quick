
#include <time.h>
#include <sys/time.h>
#include <quick/time.h>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

t_tmus timeus::current()
{
  struct ::timeval tv;
  if(0 != ::gettimeofday(&tv, nullptr))
    return nulls::time;
  return tv.tv_sec * (t_tmus)_uspersec + tv.tv_usec;
}

timedate timeus::date(t_tmus t)
{
  time_t std = seconds(t);
  timedate date;
  struct ::tm dat;
  if(nullptr == ::localtime_r(&std, &dat))
    return date;
    
  date.year   = dat.tm_year + 1900;
  date.month  = dat.tm_mon + 1;
  date.day    = dat.tm_mday;
  date.hour   = dat.tm_hour;
  date.minute = dat.tm_min;
  date.second = dat.tm_sec;
  date.us     = usec(t);
  return date;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

t_tmsec timesec::current()
{
  return timeus::seconds(timeus::current());
}

timedate timesec::date(t_tmsec t)
{
  return timeus::date((t_tmus)t * timeus::_uspersec);
}

int timesec::diffdays(t_tmsec end, t_tmsec begin)
{
  return (end - begin) / (24 * 3600);
}

int timesec::diffmonths(t_tmsec end, t_tmsec begin)
{
  timedate d1 = date(end);
  timedate d2 = date(begin);
  return (d1.year * 12 + d1.month - 1) - (d2.year * 12 + d2.month - 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
}
// END
