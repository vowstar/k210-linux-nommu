/* Generated automatically by the program `genconstants'
   from the machine description file `md'.  */

#ifndef GCC_INSN_CONSTANTS_H
#define GCC_INSN_CONSTANTS_H

#define RETURN_ADDR_REGNUM 1
#define S0_REGNUM 8
#define T0_REGNUM 5
#define GP_REGNUM 3
#define NORMAL_RETURN 0
#define S2_REGNUM 18
#define S1_REGNUM 9
#define SIBCALL_RETURN 1
#define EXCEPTION_RETURN 2
#define T1_REGNUM 6

enum unspec {
  UNSPEC_EH_RETURN = 0,
  UNSPEC_ADDRESS_FIRST = 1,
  UNSPEC_PCREL = 2,
  UNSPEC_LOAD_GOT = 3,
  UNSPEC_TLS = 4,
  UNSPEC_TLS_LE = 5,
  UNSPEC_TLS_IE = 6,
  UNSPEC_TLS_GD = 7,
  UNSPEC_AUIPC = 8,
  UNSPEC_FLT_QUIET = 9,
  UNSPEC_FLE_QUIET = 10,
  UNSPEC_COPYSIGN = 11,
  UNSPEC_LRINT = 12,
  UNSPEC_LROUND = 13,
  UNSPEC_TIE = 14,
  UNSPEC_COMPARE_AND_SWAP = 15,
  UNSPEC_SYNC_OLD_OP = 16,
  UNSPEC_SYNC_EXCHANGE = 17,
  UNSPEC_ATOMIC_STORE = 18,
  UNSPEC_MEMORY_BARRIER = 19
};
#define NUM_UNSPEC_VALUES 20
extern const char *const unspec_strings[];

enum unspecv {
  UNSPECV_GPR_SAVE = 0,
  UNSPECV_GPR_RESTORE = 1,
  UNSPECV_FRFLAGS = 2,
  UNSPECV_FSFLAGS = 3,
  UNSPECV_MRET = 4,
  UNSPECV_SRET = 5,
  UNSPECV_URET = 6,
  UNSPECV_BLOCKAGE = 7,
  UNSPECV_FENCE = 8,
  UNSPECV_FENCE_I = 9
};
#define NUM_UNSPECV_VALUES 10
extern const char *const unspecv_strings[];

#endif /* GCC_INSN_CONSTANTS_H */
