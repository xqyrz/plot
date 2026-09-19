#ifndef _UNISTD_H_
#define _UNISTD_H_

#ifdef _MSC_VER
#define HAVE_SNPRINTF 1
#define HAVE_VSNPRINTF 1
#include <process.h>
#include <stdarg.h>
#define execvp _execvp
#define strcasecmp _stricmp
#define getpid _getpid
#if !defined(S_ISREG) && defined(S_IFMT) && defined(S_IFREG)
  #define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#endif

#if !defined(S_ISDIR) && defined(S_IFMT) && defined(S_IFDIR)
  #define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#endif
#endif
#endif
