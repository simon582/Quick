
#include <dirent.h>
#include <errno.h>
#include <quick/dir.h>

namespace quick {
////////////////////////////////////////////////////////////////////////////////////////////////////

void directory::files(t_constr dir, array<cstring> &subs)
{
  ::DIR *pdir = ::opendir(dir);
  if(nullptr == pdir)
    return quick_crash(errno, "BAD_OPEN_DIR: dir=%s", dir);
  
  subs.clear();
  
  cstring s;
  s.buffer(configures::bufsz_pathfilename);
  
  struct ::dirent *pd = nullptr;
  while(nullptr != (pd = ::readdir(pdir)))
  {
    if(pd->d_type & DT_DIR) continue;
    if('.' == *pd->d_name) continue;
    
    ::sprintf(s.buffer(), "%s/%s", dir, pd->d_name);
    s.fix();
    
    subs.append(s);
  }
  
  if(0 != ::closedir(pdir))
    return quick_crash(errno, "BAD_CLOSE_DIR: dir=%s", dir);
  return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
}
// END
