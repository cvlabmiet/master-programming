---
title: Master programming
subtitle: Лекция №2 (Подготовка рабочего места)
author: Игорь Шаронов
date: 2018-02-18
---

# Темы лекции {#overview}

* Операционная система Linux
* Новая эра: NixOS
* Установка NixOS
* Протокол общения SSH

---

# Операционная система Linux {#linux}

<div class='column' style='float:left'>
```
/
├── bin
├── include
├── lib
├── lib64
├── etc
├── usr
│   ├── include
│   ├── lib
│   └── lib64
├── tmp
├── var
├── run
├── proc
├── dev
├── sys
├── home
└── opt
```
</div>

<div class='column'>
* Истинная среда для программирования
* Пакетный менеджер (apt, yum, portage, aur, ...)
* Системные демоны --- `systemd`
* Большой выбор библиотек
* Поддержка многих языков программирования
* Переменные окружения (`PATH`, `USER`, ...)
* Статические и динамические библиотеки
</div>

---

# Новая эра: NixOS {#nixos-overview}

* Сайт сообщества [nixos.org](https://nixos.org)
* Пакетный менеджер --- конфигурационный скрипт `/etc/nixos/configuration.nix`
* Используется функциональный язык `nix-expression`
* Поддерживает как сборку из исходников, так и установку бинарных пакетов
* Любые бинарные пакеты поддерживаются: deb, rpm, tar.gz, ...
* **Изолированные окружения**

---

## Установка NixOS {#nixos-setup}

Установка подробно дана в [nixos-setup](nixos-setup.html)

## Настройка доступа по SSH {#nixos-install-cont}

Необходимо сделать перенаправление порта 22 гостевой системы на любой доступный порт хоста (2222, 5022 и т.д.)

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
├── authorized_keys
├── config
├── id_rsa
├── id_rsa.pub
└── known_hosts

0 directories, 4 files
```
</div>

## Настройка SSH {#ssh-setup}

Настройка алиасов
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

Добавление ключа в виртуальную машину
```
$ ssh nixos 'mkdir ~/.ssh/'
$ scp /home/igor/.ssh/id_rsa.pub nixos:~/.ssh/authorized_keys
```

---

## Проверка работоспособности окружения {#nixos-check}

Внутри виртуальной машины:
```
[guest@nixos:~]$ pkg-config --cflags --libs fuse3
-I/nix/store/r6fjssaw0ppzfd106wmjc2rlkkxyfvig-fuse-3.2.0/include/fuse3 \
-L/nix/store/r6fjssaw0ppzfd106wmjc2rlkkxyfvig-fuse-3.2.0/lib -lfuse3 -lpthread

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

---

# Задание {#task}

1. Настроить виртуальное окружение
2. Ответить на вопрос о `hardware-configuration.nix`
