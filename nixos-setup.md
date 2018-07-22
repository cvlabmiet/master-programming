---
css: GitHub.css
title: NixOS overview
---

# Установка NixOS на виртуальную машину

Расширенная инструкция по установке NixOS на виртуальную машину.
Поддерживаются виратуальные машины:

* qemu (через фронденд libvirt);
* VirtualBox;
* VMware (player);
* Parallels.

## Создание виртуальной машины

Образ для установки загружается с сайта <https://nixos.org/nixos/download.html>.
Следует выбирать Minimal installation 64-bit.
Конфигурационные файлы образа системы находятся в общем доступе на github-е.
Репозиторий с конфигурационными файлами необходимо загрузить к себе локально:
```
$ git clone https://github.com/cvlabmiet/nixos-config.git
```

Терминология:

* host --- система, на которой запущена виртуальная машина;
* guest --- система внутри виртуальной машины.

Конфигурация виртуальной машины:

* имя: `nixos`;
* 2 ядра с топологией реального процессора;
* 1ГиБ ОЗУ;
* тип сетевой карты: Usermode networking;
* 10ГиБ внешнего диска;
* совместная файловая система для доступа внутри виртуальной машины:
    * путь внутри хоста: `/home/$USER`
    * название: `shared`
    * режим: только для чтения
* если используется фронтенд `libvirt`, необходимо запускать менеджер с правами пользователя:
    * `virsh -c qemu:///session`
    * `virt-manager -c qemu:///session`

## Разметка диска

Внутри виртуальной машины делаем разметку GPT
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
Partition number (2-128, default 2):
First sector (34-20971486, default = 206848) or {+-}size{KMGTP}:
Last sector (206848-20971486, default = 20971486) or {+-}size{KMGTP}: +7G
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
Changed type of partition to 'Linux swap'

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

Далее происходит форматирование разделов.
Сначала убедимся, что диск правильно размечен:
```
[root@nixos:~]# partx /dev/sda
NR    START      END  SECTORS  SIZE NAME                UUID
 1     2048   206847   204800  100M Linux filesystem    e0951ce2-086a-48e2-bb7a-0f01771cf111
 2   206848 14886911 14680064    7G Linux filesystem    f0940803-cb22-487d-8168-a791fd352354
 3 14886912 18778111  3891200  1.9G Linux filesystem    4f281519-78cd-4824-862b-b2f5988a1b4c
 4 18778112 20971486  2193375    1G Linux swap          595abb64-0f90-453b-b278-e312586ad9a0
 5       34     2047     2014 1007K BIOS boot partition 74582d19-55f5-475b-84c7-c176e35a0ed3
```

После этого отформатируем разделы с присвоением им меток:
```
[root@nixos:~]# mkfs.ext4 -L boot /dev/sda1
[root@nixos:~]# mkfs.ext4 -L root /dev/sda2
[root@nixos:~]# mkfs.ext4 -L home /dev/sda3
[root@nixos:~]# mkswap -L swap /dev/sda4
```

## Установка

Установка будет состоять из 2-х этапов:

1. на первом этапе происходит монтирование разделов и генерация минимального конфигурационного файла для установки;
1. второй этап нужен для настройки установленной системы: монтирования файловой системы хоста и пересборка системы.

### Первый этап установки

Для начала необходимо смонтировать созданные разделы в нужном порядке.
Все смонтированные разделы будут автоматически перенесены в файл конфигурации новой системы.
Включаем swap-раздел и проверяем его работу, чтобы он мог появится в конфигурации:
```
[root@nixos:~]# swapon /dev/sda4
[root@nixos:~]# free -h
              total        used        free      shared  buff/cache   available
Mem:           997M         64M        638M         18M        295M        779M
Swap:          1.0G          0B        1.0G
```
Если в поле `Swap` появились цифры, значит swap включен.

Все оставшиеся разделы монтируем в `/mnt` по их меткам:
```
[root@nixos:~]# mount /dev/disk/by-label/root /mnt/
[root@nixos:~]# mkdir /mnt/{boot,home,shared}
[root@nixos:~]# mount /dev/disk/by-label/boot /mnt/boot
[root@nixos:~]# mount /dev/disk/by-label/home /mnt/home
```

Теперь топология файловой системы готова.
Приступаем к генерации минимальной конфигурации системы:
```
# nixos-generate-config --root /mnt
# less /mnt/etc/nixos/hardware-configuration.nix
# vim /mnt/etc/nixos/configuration.nix
```

В созданной конфигурации необходимо добавить следующее:

1. открываем файл `/mnt/etc/nixos/configuration.nix` текстовым редактором внутри гостя (доступны `nano` или `vim`);
1. заготавливаем строчку для второго этапа установки:

    ```
    imports =
        [ # Include the results of the hardware scan.
            ./hardware-configuration.nix
            #/shared/nixos-config/vm-guest.nix
        ];
    ```
1. раскомментируем строку устройства загрузки для установки grub-а:

    ```
    boot.loader.grub.device = "/dev/sda";
    ```

В `/mnt/etc/nixos/hardware-configuration.nix` необходимо проверить, что система правильно распознала виртуальную машину.

* для qemu в файле должны присутствовать строки:

    ```
    imports = [
        <nixpkgs/nixos/modules/profiles/qemu-guest.nix>
    ];
    ```
* для VritualBox должно быть написано `virtualisation.virtualbox.guest.enable = true;`
* для VMware должно быть написано `services.vmwareGuest.enable = true;`
* для Parallels --- `hardware.parallels.enable = true;`

Также в этом файле можно проверить, что все размеченные разделы на месте.

Проверим наличие интернета:
```
# curl http://google.com
<HTML><HEAD><meta http-equiv="content-type" content="text/html;charset=utf-8">
<TITLE>302 Moved</TITLE></HEAD><BODY>
<H1>302 Moved</H1>
The document has moved
<A HREF="http://www.google.ru/?gfe_rd=cr&amp;dcr=0&amp;ei=3i2hWsbEJdSDuAHZnqnACA">here</A>.
</BODY></HTML>
```

После всех проделанных шагов, можно устанавливать систему и перезагружаться:
```
# nixos-install
# reboot
```

Система предложит ввести пароль `root`-пользователя.
Можно ввести что-то простое, например, `root`.

### Второй этап установки

После перезагрузки вводим логин и пароль пользователя `root`.
Монтируем общую директорию, в зависимости от виртуальной машины:

* `mount -t 9p shared /shared` --- для qemu;
* `mount -t vboxsf shared /shared` --- для VirtualBox;
* `mount -t vmhgfs .host:/shared /shared` --- для VMware;
* `mount -t prl_fs none /shared` --- для Parallels.

После монтирования можно раскомментировать заготовленную строку в `/etc/nixos/configuration.nix`
```
imports =
    [ # Include the results of the hardware scan.
        ./hardware-configuration.nix
        /shared/nixos-config/vm-guest.nix
    ];
```

Теперь всё готово, чтобы "пересобрать" систему с новой конфигурацией:
```
$ sudo nixos-rebuild switch
```

После обновления системы необходимо выполнить перезагрузку.
Подсказка по управлению выключением линукса через systemd:

* выключение: `systemctl poweroff`;
* перезагрузка: `systemctl reboot`;
* сон: `systemctl suspend`;
* гибернация: `systemctl hibernate`;
* ускоренная перезагрузка (без выхода в BIOS): `sudo systemctl kexec`.

После перезагрузки система готова к использованию.
