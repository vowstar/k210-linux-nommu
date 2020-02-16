# k210-linux-nommu

## Introduction

This is a tutorial for beginners, mainly describes how to compile the kernel to run NOMMU linux on k210. And, this tutorial will show how to cross compile a tcc so that you can execute a C program with tcc on the k210. The kernel source is download from https://www.kernel.org, and applied [Damien Le Moal's k210 patch](https://lore.kernel.org/linux-riscv/BYAPR04MB5816C1EADCEF92F1F1DE60E0E7140@BYAPR04MB5816.namprd04.prod.outlook.com/T/#t)

## Buildroot

First we need to compile the toolchain, according to the description of A, the toolchain can be obtained through [modified buildroot](https://github.com/damien-lemoal/riscv64-nommu-buildroot).Originally planned to be added as a git submodule, but some people said that this is a tutorial for beginners, so the [buildroot source code](./riscv64-nommu-buildroot) was added to this project.

## Rootfs



## Kernel

The [linux-5.6-rc1 source](https://www.kernel.org) applied [Damien Le Moal's k210 patch](https://lore.kernel.org/linux-riscv/BYAPR04MB5816C1EADCEF92F1F1DE60E0E7140@BYAPR04MB5816.namprd04.prod.outlook.com/T/#t). 

Thank you so much for their efforts, signed-off-by commiters:

- Damien Le Moal <damien.lemoal@wdc.com>
- Anup Patel <anup.patel@wdc.com>
- Christoph Hellwig <hch@lst.de>

Originally planned to be added as a git submodule, but some people said that this is a tutorial for beginners, so the [kernel source code](./linux-kernel) was added to this project. 

In order to be able to compile smoothly, I shamelessly put the ROOTFS ``k210.cpio`` binary file into the kernel source directory. This file should not be submitted to the source directory. This is a negative example, please do not do this like me.
