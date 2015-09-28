
#include <stdarg.h>
#include <stdlib.h>
#include <quick/crash.h>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

void crashor::abort(srcinfo info, int code, t_constr msg, ...)
{
  static char message[configures::bufsz_message];
  if(nullptr == msg)
  {
    ::strcpy(message, "[null]");
  }
  else
  {
    va_list va;
    va_start(va, msg);
    ::vsnprintf(message, sizeof(message)-1, msg, va);
    message[sizeof(message)-1] = nulls::chr;
    va_end(va);
  }

  ::fprintf(stderr, _CMD_RED_"===> program crash: src=" _CMD_HILI_"%s:%s:%d"
    _CMD_RED_", err=" _CMD_HILI_"%d:%s" _CMD_RED_", msg=" _CMD_HILI_"%s" _CMD_CLEAN_"\n",
    info.srouce, info.func, info.line, code, errcode::errstr(code), message);
    
  ::exit(errcode::rela(code));
  return;
}

void crashor::assert_fail(srcinfo info, t_constr expr)
{
  return abort(info, errcode::bad_assert, "BAD_ASSERT: %s", expr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
}
// END
