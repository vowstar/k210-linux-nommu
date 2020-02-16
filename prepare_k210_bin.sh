#!/usr/bin/env sh

export PATH=/opt/riscv64-uclibc/bin:$(pwd)/riscv64-nommu-buildroot/output/host/bin:$PATH
export PROJ_ROOT="$(pwd)"
export ROOTFS="$(pwd)/rootfs_k210"
export KERNEL="$(pwd)/linux-kernel"

# safe check
[ -d "linux-kernel" ] && echo "Directory linux-kernel exists." || echo "Error: Directory linux-kernel does not exists, please cd to project root."

cd $PROJ_ROOT

if [ ! -d "rootfs_k210" ] ; then
    sh prepare_k210_cpio.sh
fi

cd $KERNEL

make ARCH=riscv CROSS_COMPILE=riscv64-linux- nommu_k210_defconfig
make ARCH=riscv CROSS_COMPILE=riscv64-linux- -j
