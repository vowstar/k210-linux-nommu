#!/usr/bin/env sh

export PATH=/opt/riscv64-uclibc/bin:$(pwd)/riscv64-nommu-buildroot/output/host/bin:$PATH
export ROOTPROJ="$(pwd)/rootfs_k210"
export ROOTFS="$(pwd)/rootfs_k210"
export KERNEL="$(pwd)/linux-kernel"

# safe check
[ -d "rootfs_k210" ] && echo "Directory rootfs_k210 exists." || echo "Error: Directory rootfs_k210 does not exists, please cd to project root."
[ -d "rootfs_k210" ] && rm -rf $KERNEL/k210.cpio || echo "Error: Please cd to project root."
[ -d "rootfs_k210" ] && rm -rf $ROOTFS/usr/share || echo "Error: Please cd to project root."

cp init $ROOTFS/bin/

# Begin Damien Le Moal's code:
# https://lore.kernel.org/linux-riscv/BYAPR04MB5816C1EADCEF92F1F1DE60E0E7140@BYAPR04MB5816.namprd04.prod.outlook.com/T/#t

# Prepare
cd $ROOTFS
mkdir dev sys proc tmp root etc
mkdir dev/pts dev/shm

cd dev
sudo mknod -m 622 console c 5 1
sudo mknod -m 666 null c 1 3
sudo mknod -m 666 zero c 1 5
sudo mknod -m 666 ptmx c 5 2
sudo mknod -m 666 tty c 5 0
sudo mknod -m 444 random c 1 8
sudo mknod -m 444 urandom c 1 9
sudo mknod -m 666 ttySIF0 c 4 64
sudo mknod -m 666 tty0 c 4 0
sudo chown root:tty {console,ptmx,tty}
cd ..

# Create image file
echo "Creating cpio image"

find . | cpio -H newc -o > $KERNEL/k210.cpio
