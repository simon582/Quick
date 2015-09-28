
#ifndef _QK_BASE_H_
#define _QK_BASE_H_
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <new>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef _interface_
#error "_interface_" already defined
#else
#define _interface_
#endif

#ifdef _crash_
#error "_crash_" already defined
#else
#define _crash_
#endif

#ifdef _nocrash_
#error "_nocrash_" already defined
#else
#define _nocrash_
#endif

#ifdef _nosafe_
#error "_nosafe_" already defined
#else
#define _nosafe_
#endif

#ifdef _XCODE_
  #ifdef _CMDCLR_
  #undef _CMDCLR_
  #endif
#else
  #ifndef _CMDCLR_
  #define _CMDCLR_
  #endif
#endif

#ifdef _DEBUG_
#ifndef _ASSERT_
#define _ASSERT_
#endif
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif
// END
