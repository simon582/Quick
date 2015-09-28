
#ifndef _QK_LOG_H_
#define _QK_LOG_H_

#include <quick/time.h>
#include <quick/string.h>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

class loggor
{
public:
  class flag
  {
  public:
    enum _flg
    {
      okay    = 0x01,
      warn    = 0x02,
      error   = 0x04,
      info    = 0x08,
      debug   = 0x10,
      dft     = info
    };
  };

protected:
  cstring _path;
  stack<char> _buf;
  t_tmus _tick = nulls::time;
public:
  inline loggor()                       { _tick = timeus::current(); }
  inline explicit loggor(t_constr path) { _tick = timeus::current(); setpath(path); }
  inline ~loggor() = default;
private:
  loggor(const loggor &) = delete;
  loggor & operator=(const loggor &) = delete;
public:
  void setpath(t_constr path);
  void putl(int flg, t_constr msg, ...);
  void putl(t_constr msg, ...);
protected:
  void putlv(int flg, t_constr msg, va_list va);
  t_str put_head(t_str buf);
  t_str get_status(t_str buf, int flg);
  t_str get_dest(t_str buf);
  
public:
  static loggor dft;
};

typedef loggor::flag logf;

////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif
// END
