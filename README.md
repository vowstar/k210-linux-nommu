# k210-linux-nommu

## Introduction

This is a tutorial for beginners, mainly describes how to compile the kernel to run NOMMU linux on k210.

And, this tutorial will show how to cross compile a tcc so that you can execute a C program with tcc on the k210.

The kernel source is download from https://www.kernel.org, and applied [Damien Le Moal's k210 patch](https://lore.kernel.org/linux-riscv/BYAPR04MB5816C1EADCEF92F1F1DE60E0E7140@BYAPR04MB5816.namprd04.prod.outlook.com/T/#t)

## Buildroot

First we need to compile the toolchain, according to the description of A, the toolchain can be obtained through [modified buildroot](https://github.com/damien-lemoal/riscv64-nommu-buildroot).

Originally planned to be added as a git submodule, but some people said that this is a tutorial for beginners, so the source code was added to this project.
