
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

Referenced post:  
[Official RT-Kernel HOWTO](https://wiki.linuxfoundation.org/realtime/documentation/howto/applications/preemptrt_setup)  
[Official Raspberry Pi Kernel Buildling](https://www.raspberrypi.org/documentation/linux/kernel/building.md)  
[A blog](https://lemariva.com/blog/2018/07/raspberry-pi-xenomai-patching-tutorial-for-kernel-4-14-y)

# 1. How to build

## 1-1. Setup

I will get files and build at `RTKERNEL_ROOT=/home/builder/local`
```
cd /home/builder/local
```

1. Get RT-Kernel from Official Raspberry Pi repository  
Raspberry Pi officailly provides branch rpi-4.14.y-rt as a RT-Kernel 4.14.71-rt44  
(It is huge. If you don't need history, you can save time with option `--depth=1`.)
```
git clone https://github.com/raspberrypi/linux.git -b rpi-4.14.y-rt
```

2. Get Build tools

I will use [RaspberryPi Tools](https://github.com/raspberrypi/tools).  
(In Docker environment, if you clone the repository not downloading the binaries, you may encounter "no such file or directory" for ARM 32bit cross compiler)
```
wget https://github.com/raspberrypi/tools/archive/master.zip -O tools-rpi.zip
unzip tools-rpi.zip
mv tools-master/ tools-rpi/
```

3. Setup env values.

**Edit** my [`build_env.sh`](https://github.com/GPRESean/ToyProjects-Embedded/blob/master/RT-Kernel/howto-build-rtkernel/build_env.sh) with your own path
```
wget https://raw.githubusercontent.com/GPRESean/ToyProjects-Embedded/master/RT-Kernel/howto-build-rtkernel/build_env.sh
vi build_env.sh
```

Execute the script
```
chmod +x build_env.sh
. build_env.sh
```

## 1-2. Build

1. Configure Linux source.
```
cd linux
```

* If you have Raspberry Pi 1/1.2 B(+), A(+), Zero (W): use `make bcmrpi_defconfig`  
* If you have Raspberry Pi 2, 3 B(+): use `make bcm2709_defconfig`  
```
make bcm2709_defconfig
```

2. Check configs  

| Name                        | Where  | Value  |
| --------------------------- | ------ | ------ |
| HIGH_RES_TIMERS             | General setup -> Timers subsystem -> High Resolution Timer Support | Enabled |
| CONFIG_PREEMPT_RT_FULL      | Kernel Features -> Preemption Model -> Fully Preemptible Kernel (RT) | Selected |
| CONFIG_HZ, HZ_100...HZ_1000 | Kernel Features -> Timer frequency | Seleted desired value |  

* Higher HZ means, lower latencies. Since higher HZ means shorter scheduling interval.
```
make menuconfig
```

3. Build Kernel for RaspberryPi
```
make -j8 zImage
make -j8 modules
make -j8 dtbs
make -j8 module_install
make -j8 dtbs_install
```

4. Make boot image
```
mkdir -p $INSTALL_MOD_PATH/boot
./scripts/mkknlimg ./arch/arm/boot/zImage $INSTALL_MOD_PATH/boot/$KERNEL.img
```

# 2. How to install

## 1. On host

1. Make tgz file of build outputs
```
cd $INSTALL_MOD_PATH
tar czf ../boot-rtkernel4.14.71-rt44.tgz *
```

2. Copy tgz file to `~/Work/` of your target device. (or your own way)
```
cd ..
scp boot-rtkernel4.14.71-rt44.tgz pi@<your device ip>:~/Work/
```

## 2. On Target device (Raspberry Pi)

1. Backup your original image.
```
cd ~/Work
mkdir -p boot-bak
cd boot-bak

sudo cp -rd /boot/*.dtb ./
sudo cp -rd /boot/cmdline.txt ./
sudo cp -rd /boot/config.txt ./

mkdir -p boot
sudo cp -rd /boot/*.img ./boot/

mkdir -p overlays
sudo cp -rd /boot/overlays/* ./overlays/

mkdir -p lib/modules
sudo cp -rd /lib/modules/$(uname -r) ./lib/modules
```

2. Install your image. (Extract tgz file)
```
cd ~/Work
mkdir -p boot-rtkernel4.14.71-rt44
cd boot-rtkernel4.14.71-rt44
tar xzf ../boot-rtkernel4.14.71-rt44.tgz
```

3. Replace boot files and kernel modules.  
**Attention1**: You can easily switch between Kernel images, if you do not replace `*.img` files in `/boot/` and preserve them by renaming your img file. You can rename your img file except `kernel.img` or `kernel7.img` and Coninue reading **Attention2**  
```
sudo cp *.dtb /boot/
sudo cp -rd ./boot/* /boot/
sudo cp -rd ./overlays/* /overlays/
sudo cp -rd ./lib/* /lib/
```

3. Add below line in `/boot/config.txt`  
Replace `<$KERNEL>` with `kernel7` depending on your `build_env.sh`  
**Attention2**: You can easily switch between Kernel images by replace `kernel=<$KERNEL>.img` with specific img file.
```
kernel=<$KERNEL>.img
device_tree=bcm2710-rpi-3-b.dtb
```

4. Add below commands in `/boot/cmdline.txt`  
Check explanation [here](https://raspberrypi.stackexchange.com/questions/4090/how-can-dwc-otg-speed-1-be-made-to-work) and [here](https://wiki.linuxfoundation.org/realtime/documentation/known_limitations#raspberry-pi-2-and-3).
```
dwc_otg.fiq_enable=0 dwc_otg.fiq_fsm_enable=0 dwc_otg.nak_holdoff=0
```

5. Reboot device.  
```
sudo reboot
```

# 3. Test installation

1. Check Kernel version.  
It will print something like `4.14.74-rt44-v7+`.
```
uname -r
```

2. Test application  
[RT-Test](https://wiki.linuxfoundation.org/realtime/documentation/howto/tools/rt-tests)  
[A blog](https://lemariva.com/blog/2018/02/raspberry-pi-rt-preempt-vs-standard-kernel-4-14-y)  

I recommend you to build this on target device  
(If you are not on target device install `libnuma-dev` too.)
```
sudo apt-get install build-essential
git clone git://git.kernel.org/pub/scm/utils/rt-tests/rt-tests.git -b stable/v1.0
cd rt-tests
make -j4 all
```

If you want to install them in your Linux system. Do below.
```
make install
```

Execute one of test programs.  
* For -l option, 50000000: 2.5 hours, 10000000: 30 minutes, 2000000: 6 minutes
```
sudo ./cyclictest -l50000000 -m -S -p90 -i200 -h400 -q > output.txt
```

Above time is from below command.
```
sudo apt-get install time
sudo \time -f "\t%E real,\t%U user,\t%S sys" ./rt-tests/cyclictest -l200000 -m -S -p90 -i200 -h400 -q > output.txt
```
