export build_root=/home/builder/local
export linux_tree=$build_root/linux-myipipe
export xenomai_root=$build_root/xenomai-3.0.7
export ipipe_file=$build_root/ipipe-core-4.14.71-arm-4_raspberrpi.patch
export out_build=$build_root/out_build

export ARCH=arm
export CROSS_COMPILE=$build_root/tools-rpi/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-
export INSTALL_MOD_PATH=$build_root/out_kernel
export INSTALL_DTBS_PATH=$build_root/out_kernel

export KERNEL=kernel7
