# What is this?
This description is about explaining how to make a latest patch of ipipe for Kernel and RaspberryPi.

Currently (2018.10.14), **ipipe-core-4.14.71-arm-4** is latest version. However you can easly make other version of ipipe patch.

[ipipe-arm GitLab repository](https://gitlab.denx.de/Xenomai/ipipe-arm)  
[Kernel for RaspberryPi GitHub repository](https://github.com/raspberrypi/linux)

## 1. How to make ipipe patch file

Clone **ipipe-arm** repository
```
git clone https://gitlab.denx.de/Xenomai/ipipe-arm.git
```

Checkout latest **ipipe-arm**
```
cd ipipe-arm
git checkout tags/ipipe-core-4.14.71-arm-4 -b ipipe-core-4.14.71-arm-4
```

Save diff of **ipipe-arm** which are from **Linux 4.14.71** to **HEAD**  
From ipipe [Linux 4.14.71](https://gitlab.denx.de/Xenomai/ipipe-arm/commit/1244bbb3e92135d247e2dddfa6fe5e3e171a9635)  
To [tags/ipipe-core-4.14.71-arm-4](https://gitlab.denx.de/Xenomai/ipipe-arm/commit/b7600fd089fdcbd5aae5385b42498259924ca2fb)
```
git diff 1244bbb3e92135d247e2dddfa6fe5e3e171a9635..HEAD > ipipe-core-4.14.71-arm-4.patch
```


## 2. How to merge ipipe changes to RaspberryPi repository + How to make ipipe patch file for RaspberryPi
Clone Linux Kernel of RaspberryPi
```
git clone https://github.com/raspberrypi/linux.git
```

Set head to **Linux 4.14.71** of RaspberryPi  
To rpi [Linux 4.14.71](https://github.com/raspberrypi/linux/commit/df493abeaf1b0a2a83ebe21262758f802e567a38)
```
git reset --hard df493abeaf1b0a2a83ebe21262758f802e567a38
```

Create a new branch from **RaspberryPi 4.14.71** for your recognition. (Since they named branch as **rpi-4.14.y**)
```
git checkout -b rpi-4.14.71
```

Create a new branch for **ipipe-arm**
```
git checkout -b rpi-4.14.71_ipipe-arm
```

Add **ipipe-arm** remote repository
```
git remote add ipipe-arm https://gitlab.denx.de/Xenomai/ipipe-arm.git
git fetch ipipe-arm
```

Cherry-pick from first commit of **ipipe-arm** after **Linux 4.14.71** to **tags/ipipe-core-4.14.71-arm-4**  
From ipipe [Linux 4.14.71](https://gitlab.denx.de/Xenomai/ipipe-arm/commit/1244bbb3e92135d247e2dddfa6fe5e3e171a9635)  
To [tags/ipipe-core-4.14.71-arm-4](https://gitlab.denx.de/Xenomai/ipipe-arm/commit/b7600fd089fdcbd5aae5385b42498259924ca2fb)
```
git cherry-pick 1244bbb3e92135d247e2dddfa6fe5e3e171a9635..tags/ipipe-core-4.14.71-arm-4
```

Resolve conflicts between **RaspberryPi Kernel** and **ipipe-arm**  
* irq-bcm2835.c
* irq-bcm2836.c
  
Open conflict file and resolve it.
```
vi <conflict file>
git add <conflict file>
```

Modify commit message and save it. Exiting editor will commit the change and continue
```
git cherry-pick --continue
```

Check results (with your eyes)
```
git log --pretty=oneline --abbrev-commit
```

Extract patch for later use. From first commit of first commit of **ipipe-arm** after **Linux 4.14.71** to HEAD  
From rpi [Linux 4.14.71](https://github.com/raspberrypi/linux/commit/df493abeaf1b0a2a83ebe21262758f802e567a38)
```
git diff df493abeaf1b0a2a83ebe21262758f802e567a38..HEAD > ipipe-core-4.14.71-arm-4_raspberrpi.patch
```
