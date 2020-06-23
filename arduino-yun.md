[<- back](README.md)

# Arduino Yun and Dragino Yun Shield
There are 3 types of applications that Room software suits very well and which require none or more or less advanced electronics knowledge (IoT, Raspberry Pi or Arduino):
1. Default passwords
2. Reboot and reset
3. Recover broken Bridge (bridge.py)
4. Upgrade linino (OpenWRT) *not recommended*
5. Install SD card
6. Install pip (SD card required)

## 1. Default passwords
* arduino
* doghunter
* dragino


## 2. Reboot and reset
Relaunch sketch:
```csharp
$ /usr/bin/reset-mcu
$ mcu-reset
$ reset-mcu
```
Reboot:
```csharp
$ /sbin/reboot -n -f
$ reboot -n -f
```
Reset to factory settings:
```csharp
$ reset-to-factory-anyway
$ reboot
```

## 3. Recover broken Bridge (bridge.py)
***bridge.py*** must be running, test:
```csharp
Using username "root".


BusyBox v1.19.4 (2015-01-06 10:25:28 CST) built-in shell (ash)
Enter 'help' for a list of built-in commands.

 ____  ____      _    ____ ___ _   _  ___
|  _ \|  _ \    / \  / ___|_ _| \ | |/ _ \
| | | | |_) |  / _ \| |  _ | ||  \| | | | |
| |_| |  _ <  / ___ \ |_| || || |\  | |_| |
|____/|_| \_\/_/   \_\____|___|_| \_|\___/

W i F i, L i n u x, M C U, E m b e d d e d

Model: Dragino v2
Version: Dragino-v2 common-2.0.7
Build Tue Nov 24 19:39:50 CST 2015

www.dragino.com
----------------------------------------------------

root@dragino-18333d:~# ps | grep .py
 1593 root       796 S    /usr/sbin/thd --socket /tmp/triggerhappy.socket --tr
15854 root      1496 S    grep .py
28578 root      5844 S    python -u bridge.py
root@dragino-18333d:~#
```

If ***bridge.py*** is broken (not running), reinstall cpu-mcu-bridge package:
```csharp
$ opkg install --force-reinstall cpu-mcu-bridge
```

## 4. Upgrade linino (OpenWRT) *not recommended*
DON'T DO UPGRADE because *python/python-mini* won't have enough free space even with 4.3M available.

Upgrade linino:
```csharp
$ opkg list-upgradable | awk -F ' - ' '{print $1}' | xargs opkg upgrade
```

## 5. Install SD card
Install SD card:
```csharp
opkg update
opkg install e2fsprogs mkdosfs fdisk rsync
;clears partition table
dd if=/dev/zero of=/dev/sda bs=4096 count=10
fdisk /dev/sda -> n, p 1, +500M,; w
umount twice with:
   umount /dev/sda?
   rm -rf /mnt/sda?
fdisk /dev/sda -> n, p 2, all available; w
umount twice with:
umount /dev/sda?
   rm -rf /mnt/sda?
   mkfs.vfat /dev/sda1
mkfs.ext4 /dev/sda2
reboot (very long > 5 min, building overlay I guess)
unpower, repower...
overlay is done, linino is resetted (old password back):
   df -h
   Filesystem                Size      Used Available Use% Mounted on
   rootfs                   14.3G    343.9M     13.2G   2% /
   /dev/root                 9.8M      9.8M         0 100% /rom
   tmpfs                    29.9M    120.0K     29.7M   0% /tmp
   tmpfs                   512.0K         0    512.0K   0% /dev
   /dev/sda2                14.3G    343.9M     13.2G   2% /overlay
   overlayfs:/overlay       14.3G    343.9M     13.2G   2% /
   /dev/sda1               499.7M         0    499.7M   0% /mnt/sda1
```

## 6. Install pip (SD card required)
Install pip (SD card required):
```csharp
opkg update  
opkg install distribute  
opkg install python-openssl  
easy_install pip
pip install crcmod
pip install trollius
```

Make Python code run much faster by pre-compiling python py modules into *pyc*, 
to compile all python modules into *pyc* issue this command:
```csharp
python -m compileall
```

Not tested yet:
Python3 on OpenWrt: Python is part of the package feeds, so you need to make sure you have 
the Packages feed configured in *feeds.conf* or *feeds.conf.default*:
```csharp
src-git packages https://github.com/openwrt/packages.git
```

And then:
```csharp
cd <your-openwrt-folder>
./scripts/feeds update packages 
./scripts/feeds install python <or python3 if you want that too>
```


## Author

**Faure Systems** (Oct 9th, 2019)
* company: FAURE SYSTEMS SAS
* mail: dev at faure dot systems
* github: <a href="https://github.com/fauresystems?tab=repositories" target="_blank">fauresystems</a>
* web: <a href="https://faure.systems/" target="_blank">Faure Systems</a>