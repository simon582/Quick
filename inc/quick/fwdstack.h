
#ifndef _QK_FWDSTACK_H_
#define _QK_FWDSTACK_H_

#include <quick/stack.h>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename _t>
class fwdstack
{
public:
  typedef _t element;
  typedef t_i64 number;
  typedef fwdstack<element> self;
  typedef stack<element> block;
protected:
  stack<block> _bucket;
  number _len = 0;
  int _blkcnt = 0;
  int _blksize = 0;
public:
  fwdstack() = default;
  explicit fwdstack(int blksize, int bktsize = configures::fwdstk_dft_bktsize)
  { init(blksize, bktsize); }
  ~fwdstack() = default;
private:
  fwdstack(const self &) = delete;
  self & operator=(const self &) = delete;
public:
  inline int bucket_size() const            { return _bucket.length(); }
  inline int block_size() const             { return _blksize; }
  inline int block_count() const            { return _blkcnt; }
  inline number length() const              { return _len; }
  inline number limit() const               { return (number)bucket_size() * block_size(); }
  inline const element & at(number i) const { return _bucket[(int)(i / _blksize)][(int)(i % _blksize)]; }
  inline element & at(number i)             { return _bucket[(int)(i / _blksize)][(int)(i % _blksize)]; }
  inline t_bytsize bytsize_block() const    { return sizeof(element) * _blksize; }
  inline t_bytsize bytsize_alloced() const  { return bytsize_block() * block_count(); }
  inline t_bytsize bytsize_used() const     { return sizeof(element) * _len; }
public:
  inline const element & operator[](number i) const { return at(i); }
  inline element & operator[](number i)             { return at(i); }
public:
  void init(int blksize, int bktsize);
  inline element * append(){ return append_series(1); }
  element * append_series(int n);
protected:
  block * append_block();
};

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename _t>
void fwdstack<_t>::init(int blksize, int bktsize)
{
  if(blksize <= 0 || bktsize <= 0)
    return quick_crash(errcode::bad_param, "INVALID_PARAM");

  if(!_bucket.isnull()) return quick_crash(errcode::bad_status, "ALREADY_INITED");
  
  _blksize  = blksize;
  
  _bucket.create(bktsize);
  
  return;
}

template<typename _t>
typename fwdstack<_t>::element * fwdstack<_t>::append_series(int n)
{
  if(n <= 0 || n > _blksize)
    quick_crash(errcode::bad_param, "NEED_COUNT_OFFSIDE: n=%d", n);
  
  int free = (_blksize - _len % _blksize) % _blksize;
  if(free <= 0 || free < n) append_block();
  
  block &blk = _bucket[_blkcnt - 1];
  quick_assert(!blk.isnull());
  
  element *p = &blk.at(_len % _blksize);
  _len += n;
  quick_assert(_len > 0);
  return p;
}

template<typename _t>
typename fwdstack<_t>::block * fwdstack<_t>::append_block()
{
  if(_blkcnt >= _bucket.length()) quick_crash(errcode::bad_status, "BUCKET_FULL");
  
  block &blk = _bucket[_blkcnt];
  quick_assert(blk.isnull());
  blk.create(_blksize);
  _len = (number)_blkcnt * _blksize;
  quick_assert(_len >= 0);
 
  _blkcnt++;
  quick_assert(_blkcnt > 0);
  return &blk;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif
