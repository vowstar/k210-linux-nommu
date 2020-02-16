/* Definitions for BSD-style memory management.
   Copyright (C) 1994-2000, 2003, 2004, 2005 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef	_SYS_MMAN_H
#define	_SYS_MMAN_H	1

#include <features.h>
#include <bits/types.h>
#define __need_size_t
#include <stddef.h>

#ifndef __off_t_defined
# ifndef __USE_FILE_OFFSET64
typedef __off_t off_t;
# else
typedef __off64_t off_t;
# endif
# define __off_t_defined
#endif

#ifndef __mode_t_defined
typedef __mode_t mode_t;
# define __mode_t_defined
#endif

#include <bits/mman.h>

/* Return value of `mmap' in case of an error.  */
#define MAP_FAILED	((void *) -1)

__BEGIN_DECLS
/* Map addresses starting near ADDR and extending for LEN bytes.  from
   OFFSET into the file FD describes according to PROT and FLAGS.  If ADDR
   is nonzero, it is the desired mapping address.  If the MAP_FIXED bit is
   set in FLAGS, the mapping will be at ADDR exactly (which must be
   page-aligned); otherwise the system chooses a convenient nearby address.
   The return value is the actual mapping address chosen or MAP_FAILED
   for errors (in which case `errno' is set).  A successful `mmap' call
   deallocates any previous mapping for the affected region.  */

#ifndef __USE_FILE_OFFSET64
extern void *mmap (void *__addr, size_t __len, int __prot,
		   int __flags, int __fd, __off_t __offset) __THROW;
#else
# ifdef __REDIRECT_NTH
extern void * __REDIRECT_NTH (mmap,
			      (void *__addr, size_t __len, int __prot,
			       int __flags, int __fd, __off64_t __offset),
			      mmap64);
# else
#  define mmap mmap64
# endif
#endif
#ifdef __USE_LARGEFILE64
extern void *mmap64 (void *__addr, size_t __len, int __prot,
		     int __flags, int __fd, __off64_t __offset) __THROW;
#endif

/* Deallocate any mapping for the region starting at ADDR and extending LEN
   bytes.  Returns 0 if successful, -1 for errors (and sets errno).  */
extern int munmap (void *__addr, size_t __len) __THROW;

/* Change the memory protection of the region starting at ADDR and
   extending LEN bytes to PROT.  Returns 0 if successful, -1 for errors
   (and sets errno).  */
extern int mprotect (void *__addr, size_t __len, int __prot) __THROW;

/* On no-mmu systems you can't have real private mappings.  */
static __inline__ int msync (void *__addr, size_t __len, int __flags) { return 0; }


/* On no-mmu systems, memory cannot be swapped out, so
 * these functions will always succeed.  */
static __inline__ int mlock (const void *__addr, size_t __len) { return 0; }
static __inline__ int munlock (const void *__addr, size_t __len) { return 0; }
static __inline__ int mlockall (int __flags) { return 0; }
static __inline__ int munlockall (void) { return 0; }

#ifdef __USE_GNU
/* Remap pages mapped by the range [ADDR,ADDR+OLD_LEN) to new length
   NEW_LEN.  If MREMAP_MAYMOVE is set in FLAGS the returned address
   may differ from ADDR.  If MREMAP_FIXED is set in FLAGS the function
   takes another paramter which is a fixed address at which the block
   resides after a successful call.  */
extern void *mremap (void *__addr, size_t __old_len, size_t __new_len,
		     int __flags, ...) __THROW;

/* Remap arbitrary pages of a shared backing store within an existing
   VMA.  */
extern int remap_file_pages (void *__start, size_t __size, int __prot,
			     size_t __pgoff, int __flags) __THROW;
#endif


/* Open shared memory segment.  */
extern int shm_open (const char *__name, int __oflag, mode_t __mode);

/* Remove shared memory segment.  */
extern int shm_unlink (const char *__name);

__END_DECLS

#endif	/* sys/mman.h */
