
#ifndef _QK_TYPES_H_
#define _QK_TYPES_H_

#include <quick/base.h>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

typedef short t_short;
typedef int t_int;
typedef long t_long;
typedef long long t_llong;
typedef unsigned short t_ushort;
typedef unsigned int t_uint;
typedef unsigned long t_ulong;
typedef unsigned long long t_ullong;

typedef int8_t t_i8;
typedef int16_t t_i16;
typedef int32_t t_i32;
typedef int64_t t_i64;
typedef uint8_t t_u8;
typedef uint16_t t_u16;
typedef uint32_t t_u32;
typedef uint64_t t_u64;

typedef unsigned char t_byt;
typedef t_byt *t_bstr;
typedef const t_byt *t_conbstr;

typedef char t_chr;
typedef t_chr *t_str;
typedef const t_chr *t_constr;

typedef void *t_ptr;
typedef const void *t_conptr;
typedef t_i64 t_bytsize;
typedef t_i64 t_ptrdiff;
typedef t_i64 t_offset;

typedef int t_hdl;

typedef t_i64 t_tmus;
typedef t_i32 t_tmsec;
typedef t_i64 t_tmspanus;
typedef t_i32 t_tmspansec;

class nulls
{
public:
  static constexpr t_chr chr          = 0;
  static constexpr t_byt byt          = 0;
  static constexpr t_bytsize bytsize  = -1;
  static constexpr t_ptrdiff ptrdiff  = 0;
  static constexpr t_offset offset    = -1;
  static constexpr t_hdl hdl          = -1;
  static constexpr int time           = -1;
  static constexpr int timespan       = 0;
};

class configures
{
public:
  static constexpr int bufsz_message                      = 256;
  static constexpr int bufsz_pathfilename                 = 256;
  static constexpr int bufsz_command                      = 256;
  static constexpr int bufsz_logline                      = 4 * 1024;
  static constexpr int fwdstk_dft_bktsize                 = 1024 * 1024;
  static constexpr int strpool_dft_blksize                = 64 * 1024 * 1024;
  static constexpr t_bytsize array_dft_min_prealloc_bytsz = 16;
  static constexpr t_bytsize array_dft_max_prealloc_bytsz = 64 * 1024 * 1024;
  static constexpr t_constr nullstr                       = "[null]";
public:
  inline static t_constr strfmt(t_constr str){ return nullptr == str ? nullstr : str; }
};

class errcode
{
public:
  enum _code
  {
    success = 0,
    _begin  = 61100,
    crashed,
    impossible,
    bad_assert,
    bad_alloc,
    bad_delete,
    bad_param,
    bad_status,
    bad_logic,
    bad_data,
    notfound,
    _end
  };
public:
  static int rela(int err);
  static t_constr errstr(int err);
};

#ifdef _CMDCLR_
#define _CMD_CLEAN_   "\033[0m"
#define _CMD_HILI_    "\033[;1m"
#define _CMD_RED_     "\033[1;31m"
#define _CMD_GREEN_   "\033[1;32m"
#define _CMD_YELLOW_  "\033[1;33m"
#define _CMD_BLUE_    "\033[1;34m"
#define _CMD_MAGE_    "\033[1;35m"
#define _CMD_CYAN_    "\033[1;36m"
#else
#define _CMD_CLEAN_
#define _CMD_HILI_
#define _CMD_RED_
#define _CMD_GREEN_
#define _CMD_YELLOW_
#define _CMD_BLUE_
#define _CMD_MAGE_
#define _CMD_CYAN_
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif
// END
