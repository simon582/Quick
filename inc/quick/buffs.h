
#ifndef _QK_BUFFS_H_
#define _QK_BUFFS_H_

#include <quick/types.h>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

class buffs
{
public:
  template<typename _t>
  inline static void zero(_t &t)
  { ::memset(&t, 0, sizeof(t)); }
  template<typename _t>
  inline static void swap(_t &a, _t &b)
  { t_byt buf[sizeof(a)]; return swap(a, b, buf); }
  template<typename _t>
  inline static void swap(_t &a, _t &b, void *tmp)
  {
    ::memcpy(tmp, &a, sizeof(_t));
    ::memcpy(&a, &b, sizeof(_t));
    ::memcpy(&b, tmp, sizeof(_t));
    return;
  }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif
// END
