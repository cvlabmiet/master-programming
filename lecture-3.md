---
title: Master programming
subtitle: Лекция №3 (Работа с git)
author: Игорь Шаронов
date: 2018-02-21
---

# Система контроля версий git {#overview}

* <https://git-scm.com> --- основной сайт с документацией по git
* <https://try.github.io> --- онлайн путеводитель по git-у
* <https://githowto.com/ru> --- ещё один путеводитель

---

# Предыстория {#pre-history}

* diff --- утилита для выяснения различий

    ```
    $ diff -u lecture-1.html lecture-2.html | head -n 20
    --- lecture-1.html 2018-02-25 14:49:23.665411221 +0300
    +++ lecture-2.html 2018-02-25 14:49:23.842322309 +0300
    @@ -4,7 +4,7 @@
       <meta name="generator" content="pandoc">
       <meta name="author" content="Игорь Шаронов">
    -  <meta name="dcterms.date" content="2018-01-15">
    +  <meta name="dcterms.date" content="2018-02-18">
       <title>Master programming</title>
       <meta name="apple-mobile-web-app-capable" content="yes">
    ```
* patch --- обратное действие diff (патч)
* конфликты:

    ```
    <<<<<<< LOCAL:sample.txt
    lines from the original file
    ======= REMOTE:sample.txt
    new lines from the patch
    >>>>>>>
    ```

---

## Внутренности git-а {#git-internals}

* Директория `.git`
    * `.git/objects/` --- пулл объектов
    * `.git/refs/` --- указатели
    * `.git/HEAD` --- указатель текущей ветки
* `git` --- файловая система ассоциативного типа
* Виды объектов: blob, tree, commit, tag
* Виды ссылок: branch, tag, remotes
* Коммит: `tree`-объект, автор, коммитер, сообщение, parent

## Хеш-суммы {#hash}

* crc32
* md5
* sha-1
* sha-2: sha-224, sha-256, cha-384, sha-512
* Быстрая идентификация сообщения/файла/пароля

    ```
    $ echo -n 'Master programming' | md5sum -
    01e171232a1aa47e9fd2ae0530782b1f  -
    $ echo -n 'master programming' | md5sum -
    e774d0115e01e1b735a7a1a9a3a85f09  -
    ```
* Коллизии хешей

---

# Повседневное использование {#git-day-by-day-usage}

* `git status`: unstaged, staged, committed
* `git add <file>` --- добавление `file` в `staged`
* `git checkout <name>` --- переход на ветку `name`
* `git checkout -b <name>` --- создание новой ветки `name`
* `git checkout -- <file>` --- отменить все изменения файла `file`
* `git reset [<commit>|<branch>]` --- перевести изменения из `committed` в состояние `unstaged`
* `git reset --hard` --- отменить все изменения (потеря данных)
* `git push [<remote>]` --- загрузка изменений на сервер `remote`
* `git push --force` --- принудительная загрузка изменений (потеря данных)
* `git diff [<commit>]` --- просмотр изменений

---

## Пример №1: добавление нескольких remote {#git-example1}

```
$ git clone git@github.com:cvlabmiet/master-programming
$ cd master-programming
master-programming $ git remote add miet git@git.miet.ru:cvlab/master-programming
master-programming $ git push miet master:master
```

```
(lecture-3 *+) $ git st
On branch lecture-3
Changes to be committed:
  (use "git reset HEAD <file>..." to unstage)

    modified:   CMakeLists.txt
    modified:   lecture-3.md

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git checkout -- <file>..." to discard changes in working directory)

    modified:   lecture-3.md
```

## Пример №2: создание локального репозитория {#git-example2}

```
$ mkdir /tmp/server
$ git init --bare /tmp/server/repo
$ cd /tmp/123/repo/
repo (BARE:master) $ ls
branches  config  description  HEAD  hooks  info  objects  refs
$ git init /tmp/repo
$ cd /tmp/repo
repo (master#) $ echo 'Empty repo' > README.md
repo (master#) $ git add README.md
repo (master#) $ git ci -am "Initial commit"
repo (master) $ git remote add origin /tmp/server/repo
repo (master) $ git push origin master:master
```

## Пример №3: сравнение с origin/master {#git-example3}

```
$ git fetch origin
$ git diff master origin/master
$ git show origin/master:lecture-3.md | less
$ git co origin/master -b new-feature
```

---

# Разрешение конфликтов {#git-conflicts}

* `LOCAL` --- локальные изменения текущей ветки
* `REMOTE` --- изменения на сервере
* `BASE` --- общий предок `LOCAL` и `REMOTE`
* `MERGED` --- автоматическое разрешение конфликта
* merge --- это тоже коммит
* Утилиты для разрешения конфликтов: vimdiff, kdiff3, meld, tortoisemerge

<div class='column' style='float:center'>
```
┌───────┬──────┬────────┐   ┌────────┬────────┐
│ LOCAL │ BASE │ REMOTE │   │        │        │
├───────┴──────┴────────┤   │ MERGED │ REMOTE │
│        MERGED         │   │        │        │
└───────────────────────┘   └────────┴────────┘
```
</div>

---

# Стратегии слияния веток {#git-merge}

<div class='column'>
```
      A---B---C topic
     /
D---E---F---G master
```
</div>

* merge no-fast-forward (`git merge --no-ff`)

    ```
          A---B---C topic
         /         \
    D---E---F---G---H master
    ```
* merge fast-forward (`git merge --ff`)

    ```
    D---E-A-F-B-G-C master
    ```
* merge squash (`git merge --squash`)

    ```
    D---E---F---G---T master
    ```
* rebase (`git rebase master`)

    ```
                  A---B---C topic
                 /
    D---E---F---G master
    ```
