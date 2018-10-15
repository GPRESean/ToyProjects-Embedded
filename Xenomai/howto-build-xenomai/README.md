
# 0. Requirements
Build Environment: Docker Ubuntu 18.04 or Ubuntu 18.04  
Cross Compiler: arm-linux-gnueabihf- 4.8.3  
Target Device: Raspberry Pi 3B  

If you want to use Docker. You can use my Dockerfile. [Link](https://github.com/GPRESean/ToyProjects-Embedded/blob/master/RT-Kernel/howto-build-rtkernel/Dockerfile)  
Default user:pwd are builder:builder
```
wget https://raw.githubusercontent.com/GPRESean/ToyProjects-Embedded/master/RT-Kernel/howto-build-rtkernel/Dockerfile
docker build -t ubuntu/builder:latest .
docker run -it -v <host path>:<container path> --name rt-builder ubuntu/builder:latest
```

Referenced post: [Link](https://lemariva.com/blog/2018/07/raspberry-pi-preempt-rt-patching-tutorial-for-kernel-4-14-y)

# 1. Build step - Kernel, Cobalt

## Setup

I will get files and build at `${build_root}` == `/home/builder/local`
```
cd /home/builder/local
```

### Get Linux Kernel

Clone Linux Kernel of RaspberryPi
```
cd ${build_root}
git clone https://github.com/raspberrypi/linux.git linux-myipipe
```

Set head to **Linux 4.14.71** of RaspberryPi  
To rpi [Linux 4.14.71](https://github.com/raspberrypi/linux/commit/df493abeaf1b0a2a83ebe21262758f802e567a38)
```
cd linux-myipipe
git reset --hard df493abeaf1b0a2a83ebe21262758f802e567a38
```

Create a new branch for **ipipe-arm**
```
git checkout -b rpi-4.14.71_ipipe-arm
```

### Get Build tools

I will use [RaspberryPi Tools](https://github.com/raspberrypi/tools).
```
cd ${build_root}
wget https://github.com/raspberrypi/tools/archive/master.zip -O tools-rpi.zip
unzip tools-rpi.zip
mv tools-master/ tools-rpi/
```

### Get Xenomai

```
cd ${build_root}
wget http://xenomai.org/downloads/xenomai/stable/xenomai-3.0.7.tar.bz2
tar xf xenomai-3.0.7.tar.bz2
```

### Get ipipe patch.

I recommend you to use a patch wich I created.
(Original patch will cause conflicts on irq-bcm2835.c and irq-bcm2836.c)
```
wget https://raw.githubusercontent.com/GPRESean/ToyProjects-Embedded/master/Xenomai/howto-make-ipipe-patch/ipipe-core-4.14.71-arm-4_raspberrpi.patch
```

### Setup env values.

**Edit** the `build_env.sh` with your own path
```
wget https://raw.githubusercontent.com/GPRESean/ToyProjects-Embedded/master/Xenomai/howto-build-xenomai/build_env.sh
vi build_env.sh
chmod +x build_env.sh
. build_env.sh
```

## Build

Setting Linux for Xenomai. (patch the kernel with ipipe-core)
```
cd $linux_tree
$xenomai_root/scripts/prepare-kernel.sh --arch=arm --ipipe=$ipipe_file --verbose
mkdir -p ${out_build}
make O=${out_build} bcm2709_defconfig
```

Disable some options.  
**CONFIG_CPU_FREQ**, **CONFIG_CPU_IDLE**, **CONFIG_KGDB**, **CONFIG_CONTEXT_TRACKING_FORCE**  
Check explanation [here](https://gitlab.denx.de/Xenomai/xenomai/wikis/Troubleshooting#kconf). Section "Common kernel configuration issues"
```
make O=${out_build} menuconfig
```

Build Kernel for RaspberryPi
```
make O=${out_build} -j8 zImage
make O=${out_build} -j8 modules
make O=${out_build} -j8 dtbs
make O=${out_build} -j8 modules_install
make O=${out_build} -j8 dtbs_install
```

Make boot image
```
mkdir -p $INSTALL_MOD_PATH/boot
./scripts/mkknlimg ${out_build}/arch/arm/boot/zImage $INSTALL_MOD_PATH/boot/$KERNEL.img
```

## Install

### On host

Make tgz file of build outputs
```
cd $INSTALL_MOD_PATH
tar czf ../boot-xenomai3.0.7-ipipe4.14.71.tgz *
```

Copy tgz file to `~/Work/` of your target device. (or your own way)
```
scp boot-xenomai3.0.7-ipipe4.14.71.tgz pi@<your device ip>:~/Work/
```

### On target device (Raspyberry Pi)

#### Install your image

Extract tgz file.
```
cd ~/Work
mkdir -p boot-xenomai3.0.7-ipipe4.14.71
cd boot-xenomai3.0.7-ipipe4.14.71
tar xzf ../boot-xenomai3.0.7-ipipe4.14.71.tgz
```

Replace boot files and kernel modules.  
(You might want to backup your original boot files before doing it)
```
sudo cp *.dtb /boot/
sudo cp -rd ./boot/* /boot/
sudo cp -rd ./overlays/* /overlays/
sudo cp -rd ./lib/* /lib/
```

Add below line in `/boot/config.txt`  
Replace `<$KERNEL>` with `kernel7` depending on `build_env.sh`
```
kernel=<$KERNEL>.img
device_tree=bcm2710-rpi-3-b.dtb
```

Add below commands in `/boot/cmdline.txt`  
Check explanation [here](https://raspberrypi.stackexchange.com/questions/4090/how-can-dwc-otg-speed-1-be-made-to-work).
```
dwc_otg.fiq_enable=0 dwc_otg.fiq_fsm_enable=0 dwc_otg.nak_holdoff=0
```


# 2. Build step - Xenomai libraries and tools

## Build

Install requiring packages. (Should install libfuse2 before libfuse-dev like below order)
```
sudo apt-get install autoconf libtool
sudo apt-get install pkg-config
sudo apt-get install libfuse2
sudo apt-get install libfuse-dev
```

```
# Logout and Login again to new packages to work
```

Setup Xenomai libraries and tools
```
cd $xenomai_root
./scripts/bootstrap --with-core=cobalt --enable-debug=partial
./configure CFLAGS="-march=armv7-a -mfpu=vfp3" LDFLAGS="-mtune=cortex-a53" --build=i686-pc-linux-gnu --host=arm-linux-gnueabihf --with-core=cobalt --enable-smp CC=${CROSS_COMPILE}gcc LD=${CROSS_COMPILE}ld
make -j8 DESTDIR=${build_root}/out_xenomai install
```

**Attention1** You can also build and install Xenomai libraries and tools on Raspberry Pi with below commands instead.  
I recommend you to do this, even if it is a bit slow. Due to some mismatches of path and configurations.
```
sudo apt-get install autoconf libtool
cd $xenomai_root
./scripts/bootstrap --with-core=cobalt --enable-debug=partial
./configure CFLAGS="-march=armv7-a -mfpu=vfp3" LDFLAGS="-mtune=cortex-a53" --with-core=cobalt --enable-smp
make -j4 install
```


## Install

### On host

Make tgz file of build outputs
```
cd ${build_root}/out_xenomai
tar czf ../tools-xenomai3.0.7.tgz *
```

Copy tgz file to `~/Work/` of your target device. (or your own way)  
```
scp tools-xenomai3.0.7.tgz pi@<your device ip>:~/Work/
```

### On target device (Raspyberry Pi)

Uncompress to /dev/, /usr/
```
cd ~/Work
sudo su
cp tools-xenomai3.0.7-ipipe4.14.71.tgz /
cd /
tar xzf tools-xenomai3.0.7.tgz
rm tools-xenomai3.0.7.tgz
exit
```

#### Edit xeno-config

Correct the path of compiler.  
(Like above **Attention1**. If you built Xenomai libraries and tools on Raspberry Pi direcly, you can skip this.)
```
vi /usr/xenomai/bin/xeno-config
```

Replace a line like below
```
XENO_CC="gcc"
```

#### Add Xenomai lib to Linux system

Create xenomai ld conf file
```
sudo vi /etc/ld.so.conf.d/xenomai.conf
```

Add below lines
```
/usr/xenomai/lib
```

Update ld
```
sudo ldconfig
```

Check ld
```
sudo ldconfig -v
```

#### Add Xenomai executable path to $PATH

Edit `.profile` (or your own PATH configuration file)
```
vi .profile
```

Add below lines
```
# append PATH with xenomai executables
if [ -d "/usr/xenomai/sbin" ] ; then
    PATH="/usr/xenomai/sbin:$PATH"
fi
if [ -d "/usr/xenomai/bin" ] ; then
    PATH="/usr/xenomai/bin:$PATH"
fi
```

## Test installation

See if Xenomai Cobalt is working
```
sudo /usr/xenomai/bin/latency
```

Test if Xenomai Cobalt is working
```
sudo /usr/xenomai/bin/xeno-test
```
