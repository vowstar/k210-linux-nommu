#!/usr/bin/env sh

export KERNEL_VER="linux-5.6-rc1"
export KERNEL_PATH="riscv64-nommu-buildroot/package/kernel"

[ -d "linux-kernel" ] && echo "Directory linux-kernel exists." || echo "Error: Directory linux-kernel does not exists, please cd to project root."

rm -rf $KERNEL_VER
rm -rf "$KERNEL_VER.tar.xz"
cp -rf linux-kernel $KERNEL_VER
tar -Jcvf "$KERNEL_VER.tar.xz" $KERNEL_VER
mkdir -p $KERNEL_PATH
mv "$KERNEL_VER.tar.xz" $KERNEL_PATH/
rm -rf $KERNEL_VER

