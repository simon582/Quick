
extern "C" {
#include "../md5-1.3.0/md5.h"
}
#include <quick/crash.h>
#include <quick/mymd5.h>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

t_ullong md5::toull(const void *buf, t_bytsize sz)
{
  unsigned char sig[MD5_SIZE];
  md5_t md5;
 
  md5_init(&md5);
  md5_process(&md5, buf, (unsigned int)sz);
  md5_finish(&md5, sig);
  
  t_ullong n = 0;
  memcpy(&n, sig, sizeof(n));
  return n;
}

t_constr md5::tostr(t_str dest, int n, const void *buf, t_bytsize sz)
{
  if(n <= 1) quick_crash(errcode::bad_param, "DEST_BUFF_TO_LESS: n=%d", n);

  unsigned char sig[MD5_SIZE];
  md5_t md5;
 
  md5_init(&md5);
  md5_process(&md5, buf, (unsigned int)sz);
  md5_finish(&md5, sig);
  
  md5_sig_to_string(sig, dest, n-1);
  dest[n-1]=nulls::chr;
  return dest;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
}
// END
