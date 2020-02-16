Buildrrot for RISC-V 64 NOMMU
=============================

Buildroot is a simple, efficient and easy-to-use tool to generate embedded
Linux systems through cross-compilation.

The documentation can be found in docs/manual. You can generate a text
document with 'make manual-text' and read output/docs/manual/manual.text.
Online documentation can be found at http://buildroot.org/docs.html

To build and use the buildroot stuff, do the following:

1) run 'make menuconfig'
2) select the target architecture and the packages you wish to compile
3) run 'make'
4) wait while it compiles
5) find the kernel, bootloader, root filesystem, etc. in output/images

You do not need to be root to build or run buildroot.  Have fun!

Buildroot comes with a basic configuration for a number of boards. Run
'make list-defconfigs' to view the list of provided configurations.

Please feed suggestions, bug reports, insults, and bribes back to the
buildroot mailing list: buildroot@buildroot.org
You can also find us on #buildroot on Freenode IRC.

If you would like to contribute patches, please read
https://buildroot.org/manual.html#submitting-patches

For riscv64 nommu uClibc toolchain build
========================================

```
$ make riscv64_nommu_defconfig
$ make
```

The compiled toolchain is in `output/host`. Copy this somewhere:

```
$ sudo cp -r output/host /opt/riscv64-uclibc
```

To compile a minimal busybox suitable for low-memory nommu system, use this
toolchain together with the minimal configuration file provided.

```
$ cd riscv64-uclibc-nommu/
$ git clone git://git.busybox.net/busybox.git
$ cd busybox
$ make buildroot/riscv64-uclibc-nommu/busybox-small.config
$ make SKIP_STRIP=y
$ make install
```

The base files usable for an initramfs image can be found in the directory
`_install/`.

For conveniance, a precompiled toolchain, a set of initramfs files and its cpio
image file are present in the riscv64-uclibc-nommu directory.

For Kendryte K210 boards
========================

The built (or precompiled) initramfs cpio image file can be used as the default
k210.cpio initramfs builtin the kernel (as referenced by nommu_k210_defconfig).

