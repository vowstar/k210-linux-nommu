.text
	.globl	_start
	.type	_start,%function

	.weak _init
	.weak _fini

_start:
	call  .load_gp
	mv    a5, a0  /* rtld_fini.  */
	/* main may be in a shared library.  */
	la   a0, main
	ld   a0, 0(sp)      /* argc.  */
	addi  a1, sp, 8  /* argv.  */

	jal _entry

	.size	_start,.-_start

/* Dynamic links need the global pointer to be initialized prior to calling
   any shared library's initializers, so we use preinit_array to load it.
   This doesn't cut it for static links, though, since the global pointer
   needs to be initialized before calling __libc_start_main in that case.
   So we redundantly initialize it at the beginning of _start.  */

.load_gp:
.option push
.option norelax
	lla   gp, __global_pointer$
.option pop
	ret

	.section .preinit_array,"aw"
	.dc.a .load_gp

/* Define a symbol for the first piece of initialized data.  */
	.data
	.globl __data_start
__data_start:
	.weak data_start
	data_start = __data_start
