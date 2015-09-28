
#include <stdlib.h>
#include <quick/crash.h>
#include <quick/strs.h>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

int strs::toint(t_constr str)
{
  bool succ = false;
  int val = toint(str, succ);
  if(!succ) quick_crash(errcode::bad_param, "BAD_STR_TO_INT: str=%s", str);
  return val;
}

int strs::toint(t_constr str, int err)
{
  bool succ = false;
  int val = toint(str, succ);
  return succ ? val : err;
}

int strs::toint(t_constr str, bool &succ)
{
  succ = false;
  char *end = nullptr;
  int val = (int)::strtol(str, &end, 10);
  if(nulls::chr != *end) return 0;
  succ = true;
  return val;
}

t_i64 strs::toi64(t_constr str)
{
  bool succ = false;
  t_i64 val = toi64(str, succ);
  if(!succ) quick_crash(errcode::bad_param, "BAD_STR_TO_INT64: str=%s", str);
  return val;
}

t_i64 strs::toi64(t_constr str, int err)
{
  bool succ = false;
  t_i64 val = toi64(str, succ);
  return succ ? val : err;
}

t_i64 strs::toi64(t_constr str, bool &succ)
{
  succ = false;
  char *end = nullptr;
  t_i64 val = (t_i64)::strtoll(str, &end, 10);
  if(nulls::chr != *end) return 0;
  succ = true;
  return val;
}

double strs::todouble(t_constr str)
{
  bool succ = false;
  int val = todouble(str, succ);
  if(!succ) quick_crash(errcode::bad_param, "BAD_STR_TO_DOUBLE: str=%s", str);
  return val;
}

double strs::todouble(t_constr str, double err)
{
  bool succ = false;
  int val = todouble(str, succ);
  return succ ? val : err;
}

double strs::todouble(t_constr str, bool &succ)
{
  succ = false;
  char *end = nullptr;
  double val = ::strtod(str, &end);
  if(nulls::chr != *end) return 0;
  succ = true;
  return val;
}

t_constr strs::numbers(t_str str)
{
  t_str p1 = str;
  t_str p2 = str;
  for(; nulls::chr != *p2; ++p2)
    if('0' <= *p2 && *p2 <= '9') *(p1++) = *p2;
  *p1 = nulls::chr;
  return str;
}

static constexpr t_bytsize _1KB = 1024;
static constexpr t_bytsize _1MB = _1KB * _1KB;
static constexpr t_bytsize _1GB = _1KB * _1MB;
static constexpr t_bytsize _1TB = _1KB * _1GB;
static constexpr t_bytsize _1PB = _1KB * _1TB;
t_constr strs::bytes_fmt(t_str buf16, t_bytsize sz)
{
  if(sz >= _1PB) sprintf(buf16, "%.1fPB", (double)sz / _1PB);
  else if(sz >= _1TB) sprintf(buf16, "%.1fTB", (double)sz / _1TB);
  else if(sz >= _1GB) sprintf(buf16, "%.1fGB", (double)sz / _1GB);
  else if(sz >= _1MB) sprintf(buf16, "%.1fMB", (double)sz / _1MB);
  else if(sz >= _1KB) sprintf(buf16, "%.1fKB", (double)sz / _1KB);
  else sprintf(buf16, "%dB", (int)sz);
  return buf16;
}

t_constr strs::bytes_fmt(t_bytsize sz)
{
  static char buf[16];
  return bytes_fmt(buf, sz);
}

static constexpr t_tmus _1MS = 1000;
static constexpr t_tmus _1SECOND = 1000 * _1MS;
static constexpr t_tmus _1MINUTE = 60 * _1SECOND;
static constexpr t_tmus _1HOUR = 60 * _1MINUTE;
static constexpr t_tmus _1DAY = 24 * _1HOUR;
t_constr strs::timespan_fmt(t_str buf16, t_tmus usec)
{
  if(usec >= _1DAY) sprintf(buf16, "%dd%dh%dm",
    (int)(usec / _1DAY), (int)(usec / _1HOUR) % 24, (int)(usec / _1MINUTE) % 60);
  else if(usec >= _1HOUR) sprintf(buf16, "%dh%dm%ds",
    (int)(usec / _1HOUR), (int)(usec / _1MINUTE) % 60, (int)(usec / _1SECOND) % 60);
  else if(usec >= _1MINUTE) sprintf(buf16, "%dm%ds",
    (int)(usec / _1MINUTE), (int)(usec / _1SECOND) % 60);
  else if(usec >= _1SECOND) sprintf(buf16, "%.3fs", (float)(usec * 1.0 / _1SECOND));
  else if(usec >= _1MS) sprintf(buf16, "%.1fms", (float)(usec * 1.0 / _1MS));
  else sprintf(buf16, "%dus", (int)usec);
  return buf16;
}

t_constr strs::timespan_fmt(t_tmspanus usec)
{
  static char buf[16];
  return timespan_fmt(buf, usec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
}
// END
