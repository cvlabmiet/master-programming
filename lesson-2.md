---
title: Master programming
subtitle: Лекция №2
author: Игорь Шаронов
date: 2018-02-18
---

# Темы лекции {#overview}

* Операционная система Linux
* Новая эра: NixOS
* Среда эмуляции `libvirt`
* Установка NixOS
* Протокол общения SSH

---

# Новая эра: NixOS {#nixos-overview}

* Сайт сообщества [nixos.org](https://nixos.org)
* Пакетный менеджер --- конфигурационный скрипт `/etc/nixos/configuration.nix`
* Используется функциональный язык `nix-expression`
* Поддерживает как сборку из исходников, так и установку бинарных пакетов
* Любые бинарные пакеты поддерживаются: deb, rpm, tar.gz, ...
* **Изолированные окружения**

---

# libvirt {#libvirt}

* Библиотека для эмуляции
* Поддерживаются виртуальные машины: VirtualBox, VMware, qemu, ...
* Пользовательские интерфейсы: virsh, virt-manager
* По настройке не отличается от других VM

---

## Установка NixOS {#nixos-setup}

* Образ для установки на странице https://nixos.org/nixos/download.html
* Следует выбирать Minimal installation 64-bit
* Конфигурационные файлы:
    ```
    $ git clone
    ```

## Конфигурация виртуальной машины {#nixos-configuration}

* Name: nixos
* 2 ядра с топологией реального процессора
* 1ГиБ ОЗУ
* Тип сетевой карты: Usermode networking
* 10ГиБ внешнего диска
* Shared filesystem для доступа внутри виртаулки:
    * mode: passthroug
    * source path: /home/<user>
    * target path: shared (readonly)

## Разбиение диска {#nixos-gptdisk}

Таблица GPT
```
[root@nixos:~]# gdisk /dev/sda
GPT fdisk (gdisk) version 1.0.1

Partition table scan:
  MBR: not present
  BSD: not present
  APM: not present
  GPT: not present

Creating new GPT entries.

Command (? for help): p
Disk /dev/sda: 20971520 sectors, 10.0 GiB
Logical sector size: 512 bytes
Disk identifier (GUID): F7108B11-6D52-425D-B7AD-FA3715663728
Partition table holds up to 128 entries
First usable sector is 34, last usable sector is 20971486
Partitions will be aligned on 2048-sector boundaries
Total free space is 20971453 sectors (10.0 GiB)

Number  Start (sector)    End (sector)  Size       Code  Name

Command (? for help): o
This option deletes all partitions and creates a new protective MBR.
Proceed? (Y/N): Y

Command (? for help): n
Partition number (1-128, default 1):
First sector (34-20971486, default = 2048) or {+-}size{KMGTP}:
Last sector (2048-20971486, default = 20971486) or {+-}size{KMGTP}: +100M
Current type is 'Linux filesystem'
Hex code or GUID (L to show codes, Enter = 8300):
Changed type of partition to 'Linux filesystem'

Command (? for help): n
Partition number (3-128, default 3):
First sector (34-20971486, default = 14886912) or {+-}size{KMGTP}: +2G
Last sector (19081216-20971486, default = 20971486) or {+-}size{KMGTP}:
Current type is 'Linux filesystem'
Hex code or GUID (L to show codes, Enter = 8300):
Changed type of partition to 'Linux filesystem'

Command (? for help): n
Partition number (3-128, default 3):
First sector (34-20971486, default = 14886912) or {+-}size{KMGTP}:
Last sector (14886912-20971486, default = 20971486) or {+-}size{KMGTP}: +1900M
Current type is 'Linux filesystem'
Hex code or GUID (L to show codes, Enter = 8300):
Changed type of partition to 'Linux filesystem'

Command (? for help): n
Partition number (4-128, default 4):
First sector (34-20971486, default = 18778112) or {+-}size{KMGTP}:
Last sector (18778112-20971486, default = 20971486) or {+-}size{KMGTP}:
Current type is 'Linux filesystem'
Hex code or GUID (L to show codes, Enter = 8300): 8200
Changed type of partition to 'Linux filesystem'

Command (? for help): n
Partition number (5-128, default 5):
First sector (34-2047, default = 34) or {+-}size{KMGTP}:
Last sector (34-2047, default = 2047) or {+-}size{KMGTP}: 
Current type is 'Linux filesystem'
Hex code or GUID (L to show codes, Enter = 8300): L
0700 Microsoft basic data  0c01 Microsoft reserved    2700 Windows RE          
3000 ONIE boot             3001 ONIE config           3900 Plan 9              
4100 PowerPC PReP boot     4200 Windows LDM data      4201 Windows LDM metadata
4202 Windows Storage Spac  7501 IBM GPFS              7f00 ChromeOS kernel     
7f01 ChromeOS root         7f02 ChromeOS reserved     8200 Linux swap          
8300 Linux filesystem      8301 Linux reserved        8302 Linux /home         
8303 Linux x86 root (/)    8304 Linux x86-64 root (/  8305 Linux ARM64 root (/)
8306 Linux /srv            8307 Linux ARM32 root (/)  8400 Intel Rapid Start   
8e00 Linux LVM             a500 FreeBSD disklabel     a501 FreeBSD boot        
a502 FreeBSD swap          a503 FreeBSD UFS           a504 FreeBSD ZFS         
a505 FreeBSD Vinum/RAID    a580 Midnight BSD data     a581 Midnight BSD boot   
a582 Midnight BSD swap     a583 Midnight BSD UFS      a584 Midnight BSD ZFS    
a585 Midnight BSD Vinum    a600 OpenBSD disklabel     a800 Apple UFS           
a901 NetBSD swap           a902 NetBSD FFS            a903 NetBSD LFS          
a904 NetBSD concatenated   a905 NetBSD encrypted      a906 NetBSD RAID         
ab00 Recovery HD           af00 Apple HFS/HFS+        af01 Apple RAID          
af02 Apple RAID offline    af03 Apple label           af04 AppleTV recovery    
af05 Apple Core Storage    bc00 Acronis Secure Zone   be00 Solaris boot        
bf00 Solaris root          bf01 Solaris /usr & Mac Z  bf02 Solaris swap        
bf03 Solaris backup        bf04 Solaris /var          bf05 Solaris /home       
bf06 Solaris alternate se  bf07 Solaris Reserved 1    bf08 Solaris Reserved 2  
Press the <Enter> key to see more codes: 
bf09 Solaris Reserved 3    bf0a Solaris Reserved 4    bf0b Solaris Reserved 5  
c001 HP-UX data            c002 HP-UX service         ea00 Freedesktop $BOOT   
eb00 Haiku BFS             ed00 Sony system partitio  ed01 Lenovo system partit
ef00 EFI System            ef01 MBR partition scheme  ef02 BIOS boot partition 
f800 Ceph OSD              f801 Ceph dm-crypt OSD     f802 Ceph journal        
f803 Ceph dm-crypt journa  f804 Ceph disk in creatio  f805 Ceph dm-crypt disk i
fb00 VMWare VMFS           fb01 VMWare reserved       fc00 VMWare kcore crash p
fd00 Linux RAID            
Hex code or GUID (L to show codes, Enter = 8300): ef02
Changed type of partition to 'BIOS boot partition'

Command (? for help): p
Disk /dev/sda: 20971520 sectors, 10.0 GiB
Logical sector size: 512 bytes
Disk identifier (GUID): A658572D-4D21-4860-A6E3-3D7245B049AF
Partition table holds up to 128 entries
First usable sector is 34, last usable sector is 20971486
Partitions will be aligned on 2-sector boundaries
Total free space is 0 sectors (0 bytes)

Number  Start (sector)    End (sector)  Size       Code  Name
   1            2048          206847   100.0 MiB   8300  Linux filesystem
   2          206848        14886911   7.0 GiB     8300  Linux filesystem
   3        14886912        18778111   1.9 GiB     8300  Linux filesystem
   4        18778112        20971486   1.0 GiB     8200  Linux swap
   5              34            2047   1007.0 KiB  EF02  BIOS boot partition

Command (? for help): w

Final checks complete. About to write GPT data. THIS WILL OVERWRITE EXISTING
PARTITIONS!!

Do you want to proceed? (Y/N): Y
OK; writing new GUID partition table (GPT) to /dev/sda.
The operation has completed successfully.

[root@nixos:~]#
```

## Настройка файловой системы {#nixos-filesystem}

```
[root@nixos:~]# gdisk -l /dev/sda
GPT fdisk (gdisk) version 1.0.1

Partition table scan:
  MBR: protective
  BSD: not present
  APM: not present
  GPT: present

Found valid GPT with protective MBR; using GPT.
Disk /dev/sda: 20971520 sectors, 10.0 GiB
Logical sector size: 512 bytes
Disk identifier (GUID): A658572D-4D21-4860-A6E3-3D7245B049AF
Partition table holds up to 128 entries
First usable sector is 34, last usable sector is 20971486
Partitions will be aligned on 2-sector boundaries
Total free space is 0 sectors (0 bytes)

Number  Start (sector)    End (sector)  Size       Code  Name
   1            2048          206847   100.0 MiB   8300  Linux filesystem
   2          206848        14886911   7.0 GiB     8300  Linux filesystem
   3        14886912        18778111   1.9 GiB     8300  Linux filesystem
   4        18778112        20971486   1.0 GiB     8200  Linux swap
   5              34            2047   1007.0 KiB  EF02  BIOS boot partition

[root@nixos:~]# mkfs.ext4 -L boot /dev/sda1
[root@nixos:~]# mkfs.ext4 -L root /dev/sda2
[root@nixos:~]# mkfs.ext4 -L home /dev/sda3
[root@nixos:~]# mkswap -L swap /dev/sda4
[root@nixos:~]# swapon /dev/sda4
[root@nixos:~]# free -h
              total        used        free      shared  buff/cache   available
Mem:           997M         64M        638M         18M        295M        779M
Swap:          1.0G          0B        1.0G

[root@nixos:~]# mkdir /shared
[root@nixos:~]# mount -t 9p shared /shared
[root@nixos:~]# ls /shared/nixos-config
core-packages.nix     gcc-packages.nix
default-settings.nix  libvirt-configuration.nix
```

## Установка {#nixos-install}

```sh
[root@nixos:~]# mount /dev/disk/by-label/root /mnt/
[root@nixos:~]# mkdir /mnt/{boot,home,shared} /shared
[root@nixos:~]# mount /dev/disk/by-label/boot /mnt/boot
[root@nixos:~]# mount /dev/disk/by-label/home /mnt/home
[root@nixos:~]# mount -t 9p shared /shared
[root@nixos:~]# nixos-generate-config --root /mnt/
writing /mnt/etc/nixos/hardware-configuration.nix...
writing /mnt/etc/nixos/configuration.nix...

<???>

[root@nixos:~]# cat /mnt/etc/nixos/configuration.nix
{ config, pkgs, ... }:

{
  imports =
    [ # Include the results of the hardware scan.
      ./hardware-configuration.nix
      /shared/nixos-config/libvirt-configuration.nix
    ];
}

[root@nixos:~]# mkdir /mnt/temp-nix
[root@nixos:~]# cp -r /nix/.rw-store/* /mnt/temp-nix/
[root@nixos:~]# mount --rbind /mnt/temp-nix /nix/.rw-store
[root@nixos:~]# df -h
Filesystem      Size  Used Avail Use% Mounted on
devtmpfs         50M     0   50M   0% /dev
tmpfs           499M     0  499M   0% /dev/shm
tmpfs           250M  3.8M  246M   2% /run
tmpfs           499M  280K  499M   1% /run/wrappers
tmpfs           499M   17M  483M   4% /
/dev/root       335M  335M     0 100% /iso
/dev/loop0      309M  309M     0 100% /nix/.ro-store
tmpfs           2.0G  499M  1.6G  25% /nix/.rw-store
unionfs         2.4G  808M  1.6G  35% /nix/store
tmpfs           499M     0  499M   0% /sys/fs/cgroup
tmpfs           100M     0  100M   0% /run/user/0
/dev/sda2       6.9G   32M  6.5G   1% /mnt
/dev/sda1        93M  1.6M   85M   2% /mnt/boot
/dev/sda3       1.8G  5.6M  1.7G   1% /mnt/home
shared          397G  278G   99G  74% /mnt/shared

[root@nixos:~]# nixos-install
[root@nixos:~]# rm -r /mnt/temp-nix
[root@nixos:~]# poweroff
```

## Установка (продолжение) {#nixos-install-cont}

```
$ virsh edit nixos
```

```diff
--- /tmp/nixos.xml	2018-02-18 12:22:24.753601712 +0300
+++ /dev/fd/63	2018-02-18 12:23:38.123210214 +0300
@@ -1,4 +1,4 @@
-<domain type='kvm'>
+<domain type='kvm' xmlns:qemu='http://libvirt.org/schemas/domain/qemu/1.0'>
   <name>nixos</name>
   <uuid>bd0ab376-6fee-428b-a30c-f1091afbcba6</uuid>
   <memory unit='KiB'>1048576</memory>
@@ -108,4 +108,9 @@
       <address type='pci' domain='0x0000' bus='0x00' slot='0x08' function='0x0'/>
     </memballoon>
   </devices>
+  <qemu:commandline>
+    <qemu:arg value='-redir'/>
+    <qemu:arg value='tcp:2222::22'/>
+  </qemu:commandline>
 </domain>
+
```

## SSH {#ssh}

<div class='column' style='float:left'>
* Secure SHell --- удалённая безопасная оболочка
* Ничем не отличается от shell
* Позволяет создавать туннели:
    ```
    work -> router -> home
    ```
* Генерация личного ключа `ssh-keygen`
</div>

<div class='column'>
```
$ tree ~/.ssh/
/home/igor/.ssh/
├── config
├── id_rsa
├── id_rsa.pub
└── known_hosts

0 directories, 4 files
```
</div>

## Установка алиасов в SSH {#ssh-alias}

```
$ ssh -p 2222 guest@localhost
<Ctrl-D>
$ cat ~/.ssh/config
Host nixos
    User guest
    Hostname localhost
    Port 2222
<Ctrl-D>
$ ssh nixos
```

---

## Проверка работоспособности окружения {#nixos-check}

```
$ virsh start nixos
$ ssh nixos 'mkdir ~/.ssh/'
$ scp /home/igor/.ssh/id_rsa.pub nixos:~/.ssh/authorized_keys
$ ssh nixos
[guest@nixos:~]$ pkg-config --cflags --libs fuse3
-I/nix/store/r6fjssaw0ppzfd106wmjc2rlkkxyfvig-fuse-3.2.0/include/fuse3 -L/nix/store/r6fjssaw0ppzfd106wmjc2rlkkxyfvig-fuse-3.2.0/lib -lfuse3 -lpthread

[guest@nixos:~]$ wget https://raw.githubusercontent.com/libfuse/libfuse/master/example/cuse.c
[guest@nixos:~]$ wget https://raw.githubusercontent.com/libfuse/libfuse/master/example/cuse_client.c
[guest@nixos:~]$ wget https://raw.githubusercontent.com/libfuse/libfuse/master/example/ioctl.h
[guest@nixos:~]$ gcc -o cuse cuse.c `pkg-config --cflags --libs fuse3`
[guest@nixos:~]$ gcc -o client cuse_client.c `pkg-config --cflags --libs fuse3`
[guest@nixos:~]$ ls
client  cuse  cuse.c  cuse_client.c  ioctl.h
[guest@nixos:~]$ sudo ./cuse --name=123
[guest@nixos:~]$ ll /dev/123
crw------- 1 root root 248, 0 Feb 18 22:47 /dev/123
[guest@nixos:~]$ echo hello  | sudo ./client /dev/123 w 6
Writing 6 bytes
transferred 6 bytes (0 -> 6)

[guest@nixos:~]$ sudo ./client /dev/123 r 10
hello
transferred 6 bytes (6 -> 6)

[guest@nixos:~]$ sudo systemctl poweroff
```
