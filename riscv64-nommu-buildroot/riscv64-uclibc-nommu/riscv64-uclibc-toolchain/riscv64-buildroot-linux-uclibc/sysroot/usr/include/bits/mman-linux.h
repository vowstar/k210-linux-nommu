/* Definitions for POSIX memory map interface.  Linux generic version.
   Copyright (C) 2001-2018 Free Software Foundation, Inc.

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

#ifndef _SYS_MMAN_H
# error "Never use <bits/mman-linux.h> directly; include <sys/mman.h> instead."
#endif

/* The following definitions basically come from the kernel headers.
   But the kernel header is not namespace clean.  */


/* Protections are chosen from these bits, OR'd together.  The
   implementation does not necessarily support PROT_EXEC or PROT_WRITE
   without PROT_READ.  The only guarantees are that no writing will be
   allowed without PROT_WRITE and no access will be allowed for PROT_NONE. */

#define PROT_READ	0x1		/* Page can be read.  */
#define PROT_WRITE	0x2		/* Page can be written.  */
#define PROT_EXEC	0x4		/* Page can be executed.  */
#define PROT_NONE	0x0		/* Page can not be accessed.  */
#define PROT_GROWSDOWN	0x01000000	/* Extend change to start of
					   growsdown vma (mprotect only).  */
#define PROT_GROWSUP	0x02000000	/* Extend change to start of
					   growsup vma (mprotect only).  */

/* Sharing types (must choose one and only one of these).  */
#define MAP_SHARED	0x01		/* Share changes.  */
#define MAP_PRIVATE	0x02		/* Changes are private.  */
#ifdef __USE_MISC
# define MAP_TYPE	0x0f		/* Mask for type of mapping.  */
#endif

/* Other flags.  */
#define MAP_FIXED	0x10		/* Interpret addr exactly.  */
#ifdef __USE_MISC
# define MAP_FILE	0
# ifdef __MAP_ANONYMOUS
#  define MAP_ANONYMOUS	__MAP_ANONYMOUS	/* Don't use a file.  */
# else
#  define MAP_ANONYMOUS	0x20		/* Don't use a file.  */
# endif
# define MAP_ANON	MAP_ANONYMOUS
/* When MAP_HUGETLB is set bits [26:31] encode the log2 of the huge page size.  */
# define MAP_HUGE_SHIFT	26
# define MAP_HUGE_MASK	0x3f
#endif

/* Flags to `msync'.  */
#define MS_ASYNC	1		/* Sync memory asynchronously.  */
#define MS_SYNC		4		/* Synchronous memory sync.  */
#define MS_INVALIDATE	2		/* Invalidate the caches.  */

/* Flags for `mremap'.  */
#ifdef __USE_GNU
# define MREMAP_MAYMOVE	1
# define MREMAP_FIXED	2
#endif

/* only define for MMU targets, no-MMU does not support madvise.  */

/* Flags for `mlockall'.  */
#ifndef MCL_CURRENT
# define MCL_CURRENT	1		/* Lock all currently mapped pages.  */
# define MCL_FUTURE	2		/* Lock all additions to address
					   space.  */
# define MCL_ONFAULT	4		/* Lock all pages that are
					   faulted in.  */
#endif

#include <bits/mman-shared.h>
