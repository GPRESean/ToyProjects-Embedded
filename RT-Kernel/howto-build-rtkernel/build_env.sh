#do ". {THISFILE}"

export RTKERNEL_ROOT=/home/builder/local

export ARCH=arm

# 32bit compiler
#export CROSS_COMPILE=$RTKERNEL_ROOT/tools-rpi/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-
# 64bit compiler
export CROSS_COMPILE=$RTKERNEL_ROOT/tools-rpi/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-

export INSTALL_MOD_PATH=$RTKERNEL_ROOT/rt-kernel
export INSTALL_DTBS_PATH=$RTKERNEL_ROOT/rt-kernel

# Raspberry Pi 1/1.2 B(+), A(+), Zero (W):
#export KERNEL=kernel
# On linux source root, do "make bcmrpi_defconfig"

# Raspberry Pi 2, 3 B(+):
#export KERNEL=kernel7
export KERNEL=kernel7_rt # For multi kernel switching
# On linux source root, do "make bcm2709_defconfig"
