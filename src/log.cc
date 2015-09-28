
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>

#include <quick/strs.h>
#include <quick/log.h>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

void loggor::setpath(t_constr path)
{
  _path = path;
  return;
}

void loggor::putl(int flg, t_constr msg, ...)
{
  va_list va;
  va_start(va, msg);
  putlv(flg, msg, va);
  va_end(va);
  return;
}

void loggor::putl(t_constr msg, ...)
{
  va_list va;
  va_start(va, msg);
  putlv(flag::dft, msg, va);
  va_end(va);
  return;
}

void loggor::putlv(int flg, t_constr msg, va_list va)
{
  if(_buf.isnull()) _buf.create(configures::bufsz_logline);
  
  if(nullptr == msg) return quick_crash(errcode::bad_param, "MSG_IS_NULL");
  
  get_status(put_head(_buf), flg);
  
  ::vsprintf(_buf + strlen(_buf), msg, va);
  
  fprintf(stdout, "%s\n", _buf.buffer());
  
  char dest[configures::bufsz_pathfilename];
  get_dest(dest);
  //FILE *fp = nullptr;
  //if(nullptr == (fp = fopen(dest, "a+")))
    //return quick_crash(errno, "CAN_NOT_OPEN_LOG_FILE: %s", dest);
  //fprintf(stdout, "%s\n", _buf.buffer());
  fflush(stdout);
  //fclose(fp);
  return;
}

t_str loggor::put_head(t_str buf)
{
  int pid = (int)::getpid();
  
  t_tmus curr = timeus::current();
  t_tmus span = curr - _tick;
  _tick = curr;
  timedate date = timeus::date(curr);
  char tmspan[32];
  strs::timespan_fmt(tmspan, span);
  
  int n = ::sprintf(buf, _CMD_HILI_" [%d-%02d-%02d %02d:%02d:%02d +%s p%d] " _CMD_CLEAN_,
    date.year, date.month, date.day, date.hour, date.minute, date.second, tmspan, pid);
  return _buf + n;
}

t_str loggor::get_status(t_str buf, int flg)
{
  if(flag::okay == (flg & flag::okay))
    return strcpy(buf, _CMD_GREEN_" [okay] " _CMD_CLEAN_" ");
  else if(flag::warn == (flg & flag::warn))
    return strcpy(buf, _CMD_MAGE_" [warn] " _CMD_CLEAN_" ");
  else if(flag::error == (flg & flag::error))
    return strcpy(buf, _CMD_RED_" [error] " _CMD_CLEAN_" ");
  else if(flag::info == (flg & flag::info))
    return strcpy(buf, _CMD_HILI_" [info] " _CMD_CLEAN_" ");
  else if(flag::debug == (flg & flag::debug))
    return strcpy(buf, _CMD_YELLOW_" [debug] " _CMD_CLEAN_" ");
  else
    return strcpy(buf, "");
}

t_str loggor::get_dest(t_str buf)
{
  timedate date = timeus::date(_tick);
  if(_path.isnull() || _path.isempty())
    sprintf(buf, "%04d%02d%02d.log", date.year, date.month, date.day);
  else
    sprintf(buf, "%s/%04d%02d%02d.log", _path.buffer(), date.year, date.month, date.day);
  return buf;
}

loggor loggor::dft;

////////////////////////////////////////////////////////////////////////////////////////////////////
}
// END
