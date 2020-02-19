#include <sys/syscall.h>

long int errno;

long int syscall(long int syscall_number, long int arg1, long int arg2, long int arg3, long int arg4, long int arg5,
                 long int arg6, long int arg7);

#define INTERNAL_SYSCALL_NCS(name, nr, args...)	\
  ({ long _sys_result;					\
     {							\
	register long int _a7 __asm__ ("a7");		\
	LOAD_ARGS_##nr (args)				\
	_a7 = (name);					\
							\
        __asm__ volatile (				\
		"scall\n\t"				\
		: "=r" (_a0) 				\
		: "r"(_a7) ASM_ARGS_##nr  		\
		: "memory"); 				\
	_sys_result = _a0;				\
     } 							\
     _sys_result; 					\
  })

/* Macros for setting up inline __asm__ input regs */
# define ASM_ARGS_0
# define ASM_ARGS_1	, "r" (_a0)
# define ASM_ARGS_2	ASM_ARGS_1, "r" (_a1)
# define ASM_ARGS_3	ASM_ARGS_2, "r" (_a2)
# define ASM_ARGS_4	ASM_ARGS_3, "r" (_a3)
# define ASM_ARGS_5	ASM_ARGS_4, "r" (_a4)
# define ASM_ARGS_6	ASM_ARGS_5, "r" (_a5)
# define ASM_ARGS_7	ASM_ARGS_6, "r" (_a6)

/* Macros for converting sys-call wrapper args into sys call args */
# define LOAD_ARGS_0()				\
  register long _a0 __asm__ ("a0");
# define LOAD_ARGS_1(a0)			\
  long _a0tmp;					\
  LOAD_ARGS_0 ()				\
  _a0tmp = (long) (a0);				\
  _a0 = _a0tmp;
# define LOAD_ARGS_2(a0, a1)			\
  register long _a1 __asm__ ("a1");		\
  long _a1tmp;					\
  LOAD_ARGS_1 (a0)				\
  _a1tmp = (long) (a1);				\
  _a1 = _a1tmp;
# define LOAD_ARGS_3(a0, a1, a2)		\
  register long _a2 __asm__ ("a2");		\
  long _a2tmp;					\
  LOAD_ARGS_2 (a0, a1)				\
  _a2tmp = (long) (a2);				\
  _a2 = _a2tmp;
# define LOAD_ARGS_4(a0, a1, a2, a3)		\
  register long _a3 __asm__ ("a3");		\
  long _a3tmp;					\
  LOAD_ARGS_3 (a0, a1, a2)			\
  _a3tmp = (long) (a3);				\
  _a3 = _a3tmp;
# define LOAD_ARGS_5(a0, a1, a2, a3, a4)	\
  register long _a4 __asm__ ("a4");		\
  long _a4tmp;					\
  LOAD_ARGS_4 (a0, a1, a2, a3)			\
  _a4tmp = (long) (a4);				\
  _a4 = _a4tmp;
# define LOAD_ARGS_6(a0, a1, a2, a3, a4, a5)	\
  register long _a5 __asm__ ("a5");		\
  long _a5tmp;					\
  LOAD_ARGS_5 (a0, a1, a2, a3, a4)		\
  _a5tmp = (long) (a5);				\
  _a5 = _a5tmp;
# define LOAD_ARGS_7(a0, a1, a2, a3, a4, a5, a6)\
  register long _a6 __asm__ ("a6");		\
  long _a6tmp;					\
  LOAD_ARGS_6 (a0, a1, a2, a3, a4, a5)		\
  _a6tmp = (long) (a6);				\
  _a6 = _a6tmp;

long int syscall(long int syscall_number, long int arg1, long int arg2, long int arg3, long int arg4, long int arg5,
                 long int arg6, long int arg7)
{
    long int ret;

    ret = INTERNAL_SYSCALL_NCS(syscall_number, 7, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    if ((ret < 0) && (ret >= -4095)) {
        errno = -ret;
        return -1;
    }

    return ret;
}
