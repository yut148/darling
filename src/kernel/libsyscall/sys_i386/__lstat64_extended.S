#define __SYSCALL_32BIT_ARG_BYTES 16
#include "SYS.h"

#ifndef SYS_lstat64_extended
#error "SYS_lstat64_extended not defined. The header files libsyscall is building against do not match syscalls.master."
#endif

#if defined(__i386__)
__SYSCALL2(__lstat64_extended, lstat64_extended, 4, cerror_nocancel)
#endif

