
#ifndef _QK_STRPOOL_H_
#define _QK_STRPOOL_H_

#include <quick/fwdstack.h>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

class strpool
{
protected:
  fwdstack<char> _pool;
public:
  inline strpool(): _pool(configures::strpool_dft_blksize){}
  inline explicit strpool(int blksize, int bktsize = configures::fwdstk_dft_bktsize):
    _pool(blksize, bktsize){}
  inline ~strpool() = default;
private:
  strpool(const strpool &) = delete;
  strpool & operator=(const strpool &) = delete;
public:
  inline t_bytsize bytsize_alloced() const  { return _pool.bytsize_alloced(); }
  inline t_bytsize bytsize_used() const     { return _pool.bytsize_used(); }
  inline t_constr append(t_constr str)
  { int n = (int)::strlen(str) + 1; return (t_constr)::memcpy(_pool.append_series(n), str, n); }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif
// END
