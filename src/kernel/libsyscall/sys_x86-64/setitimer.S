#define __SYSCALL_32BIT_ARG_BYTES 12
#include "SYS.h"

#ifndef SYS_setitimer
#error "SYS_setitimer not defined. The header files libsyscall is building against do not match syscalls.master."
#endif

#if defined(__x86_64__)
__SYSCALL2(setitimer, setitimer, 3, cerror_nocancel)
#endif

