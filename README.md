# k210-linux-nommu

## Introduction

This is a tutorial for beginners, mainly describes how to compile the kernel to run NOMMU linux on k210. And, this tutorial will show how to cross compile a tcc so that you can execute a C program with tcc on the k210. The kernel source is download from https://www.kernel.org, and applied [Damien Le Moal's k210 patch](https://lore.kernel.org/linux-riscv/BYAPR04MB5816C1EADCEF92F1F1DE60E0E7140@BYAPR04MB5816.namprd04.prod.outlook.com/T/#t) 

@damien-lemoal

## Before build

Before build, you should clone this project first and install the packages that buildroot depends on.

### Debian bullseye or Ubuntu 18.04.4

```bash
DEBIAN_FRONTEND=noninteractive apt-get update -qq && \
DEBIAN_FRONTEND=noninteractive apt-get install -yq \
    build-essential \
    device-tree-compiler \
    bison \
    flex \
    file \
    git \
    curl \
    wget \
    cpio \
    python \
    unzip \
    rsync \
    bc
```

### Fedora 31 or CentOS 8

```bash
RUN dnf -y update && \
    dnf -y groupinstall 'Development Tools' && \
    dnf -y --enablerepo=PowerTools install \
        autoconf \
        gperf \
        bison \
        flex \
        wget \
        curl \
        git \
        python36 \
        perl \
        sudo
```

### Git clone

```bash
git clone https://github.com/vowstar/k210-linux-nommu.git

cd k210-linux-nommu

export PROJ_ROOT=$(pwd)
```

## Buildroot

First we need to compile the toolchain, according to the description of A, the toolchain can be obtained through [modified buildroot](https://github.com/damien-lemoal/riscv64-nommu-buildroot).Originally planned to be added as a git submodule, but some people said that this is a tutorial for beginners, so the [buildroot source code](./riscv64-nommu-buildroot) was added to this project.

Original buildroot by Damien Le Moal @damien-lemoal:

https://github.com/damien-lemoal/riscv64-nommu-buildroot

### Move kernel

Run ``sh ./prepare_buildroot.sh`` to put kernel archive into ``riscv64-nommu-buildroot/package/kernel`` to prevent file not found error.

```bash
cd $PROJ_ROOT
sh ./prepare_buildroot.sh
```

### Build toolchain

Before build kernel, we should build riscv64 nommu uClibc toolchain first.

This process needs to ensure a good network connection. A lot of software is downloaded when compiling.

```bash
cd "$PROJ_ROOT/riscv64-nommu-buildroot"
make riscv64_nommu_defconfig
make
```

### Install toolchain

```bash
cd "$PROJ_ROOT/riscv64-nommu-buildroot"
sudo cp -r output/host /opt/riscv64-uclibc
export PATH=/opt/riscv64-uclibc/bin:$PATH
```

## Build Rootfs

### Busybox

This busybox clone from git://git.busybox.net/busybox.git. Originally planned to be added as a git submodule, but some people said that this is a tutorial for beginners, so the [busybox source code](./busybox) was added to this project.

I modified the ``$PROJ_ROOT/busybox/configs/k210_nommu_defconfig`` file to fit k210 nommu linux.

```bash
export PATH=/opt/riscv64-uclibc/bin:$PATH
cd "$PROJ_ROOT/busybox"
make k210_nommu_defconfig
make SKIP_STRIP=y
make SKIP_STRIP=y install
```

After install, all the data installed to ``$PROJ_ROOT/rootfs_k210``


## Build Kernel

The [linux-5.6-rc1 source](https://www.kernel.org) applied [Damien Le Moal's k210 patch](https://lore.kernel.org/linux-riscv/BYAPR04MB5816C1EADCEF92F1F1DE60E0E7140@BYAPR04MB5816.namprd04.prod.outlook.com/T/#t). 

Thank you so much for their efforts, signed-off-by commiters:

- Damien Le Moal <damien.lemoal@wdc.com>
- Anup Patel <anup.patel@wdc.com>
- Christoph Hellwig <hch@lst.de>

Originally planned to be added as a git submodule, but some people said that this is a tutorial for beginners, so the [kernel source code](./linux-kernel) was added to this project. 

In order to be able to compile smoothly, I shamelessly put the ROOTFS ``k210.cpio`` binary file into the kernel source directory. This file should not be submitted to the source directory. This is a negative example, please do not do this like me.

```bash
cd "$PROJ_ROOT/linux-kernel"
make ARCH=riscv CROSS_COMPILE=riscv64-linux- -j
```

## Play

Program the k210 board and enjoy linux. Suppose you are using Sipeed MAIX dan development board and the serial port is ``/dev/ttyUSB0``.

```bash
sudo usermod -a -G uucp $(whoami)
sudo usermod -a -G diaout $(whoami)
sudo python3 -m pip install kflash
su $(whoami)

kflash -B dan -b 3000000 -p /dev/ttyUSB0 arch/riscv/boot/loader.bin
python3 -m serial.tools.miniterm --raw --filter colorize /dev/ttyUSB0 115200
```
