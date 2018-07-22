---
title: Master programming
subtitle: Лекция №4 (CMake)
author: Игорь Шаронов
date: 2018-02-21
---

# Введение в CMake {#overview}

* <https://www.gitbook.com/book/tuannguyen68/learning-cmake-a-beginner-s-guide>
* <https://cmake.org/cmake/help/latest/index.html> --- документация
* <http://ttroy50.github.io/cmake-examples> --- примеры по CMake

---

## Структура проекта для CMake {#cmake-structure}

* `CMakeLists.txt` --- файлы CMake
* Каждая директория может содержать `CMakeLists.txt`
* Связывание с помощью `add_subdirectory`
* `add_library`, `add_executable` --- добавление основных целей (targets)
* `target_*` --- изменение свойств целей
* `add_test` --- добавление теста
* `export(package)` --- регистрирование проекта
* `include(CPack)` --- генерирование установочного пакета

## Цели по умолчанию {#cmake-default}

* all или просто `make` без целей
* rebuild\_cache --- перестройка кеша
* clean --- очистить дерево сборки от артефактов
* test --- запуск тестов
    * аналогично запуску `ctest`
* install --- установка собранных артефактов (используется в цели package)
* package --- создание пакета
    * аналогично запуску `cpack`
* `<name>` --- собирает отдельную цель `name`, созданную в `CMakeLists.txt`
* help --- выводит доступные цели

---

## Синтаксис CMake {#cmake-syntax}

* Идентификаторы переменных такие же, как в C++
* Имена функций и макросов регистронезависимы
* Основные структуры языка:
    * условные операторы и циклы
    * функции и макросы
    * модули (`include`)
* Точка входа --- файл `CMakeLists.txt`
* Режимы запуска
    * `cmake <dir>` --- запускает `<dir>/CMakeLists.txt`
    * `cmake -P <script>` --- режим скрипта
    * `cmake -E <cmd>` --- командный режим
    * другие режимы

## Переменные {#cmake-variables}

* `VAL` --- имя переменной
* `${VAL}` --- разыменование переменной, её значение
* `set(VAL "123 value")` --- установка значения переменной
* `set(VAL 1 2 3) === set(VAL "1;2;3")` --- списки
* Значение переменных можно передавать в строке ввода:

    ```
    $ cmake -DMYVAL="value" -DMYVAL2=123 -DMYVAL3=ON
    ```
* `option(MYVAL "Опциональная переменная" ON)` --- может быть `ON`, `OFF`
* `$ENV{HOME}` --- доступ к переменным окружения
* Важные переменные: `CMAKE_PREFIX_PATH`, `CMAKE_PROGRAM_PATH`, `CMAKE_TOOLCHAIN_FILE`
* Стандартные переменные: `CMAKE_SOURCE_DIR`, `CMAKE_CURRENT_SOURCE_DIR`, `CMAKE_BINARY_DIR`,
`CMAKE_CURRENT_BINARY_DIR`, `CMAKE_CURRENT_LIST_DIR`

---

## MWE {#cmake-mwe1}

```cmake
cmake_minimum_required(VERSION 3.9)
project(example VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "la-la-la")

set(CMAKE_CXX_STANDARD 17)

include(CTest)

file(GLOB SOURCES src/*.cpp)
add_library(unit STATIC ${SOURCES}) # libunit.a
target_include_directories(unit PUBLIC include)

add_executable(example app/main.cpp)
target_link_libraries(example PUBLIC unit m dl)

add_test(NAME simple_test COMMAND example --filter sim --dir /tmp)
set_tests_properties(simple_test PROPERTIES PASS_REGULAR_EXPRESSION "hello world")
```

## Пример создания пакета {#cmake-packet}

```cmake
include(GNUInstallDirs)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS example unit
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

list(APPEND CPACK_GENERATOR TGZ)
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_SYSTEM_NAME ${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR})
set(CPACK_PACKAGE_CONTACT "MIET")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libfuse3 (>= 3.2.0)")
include(CPack)
```

---

## Экспорты {#cmake-export}

* Связывание проектов можно осуществить с помощью экспорта целей
* `find_package` позволяет осуществить подключение сторонних целей
* В CMake есть локальный реестр пакетов (`~/.cmake/packages`)
* С помощью `find_package` и `CMAKE_MODULE_PATH` можно экпортировать существующие библиотеки

## Install-дерево и export {#cmake-install-tree}

```cmake
target_include_directories(unit PUBLIC $<INSTALL_INTERFACE:include> $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>)

install(TARGETS example unit EXPORT ${PROJECT_NAME}-config
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(EXPORT ${PROJECT_NAME}-config NAMESPACE my:: DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME})

export(TARGETS example unit NAMESPACE my:: FILE ${PROJECT_NAME}-config.cmake)
export(PACKAGE ${PROJECT_NAME})
```

* Локальное дерево сборки:
    * `export(TARGETS ...)` --- создание экспорт-файла в дереве сборки
    * `export(PACKAGE ...)` --- создание ссылки в локальном реестре на каталог сборки
* Install-дерево:
    * `install(TARGETS ... EXPORT ...)` --- прописывание таргетов в экспорте
    * `install(EXPORT ...)` --- установка экспорт-файла

## Использование в стороннем проекте {#cmake-external-project-usage}

```cmake
find_package(example REQUIRED)

add_executable(myprog ${SRCS})
target_link_libraries(myprog my::unit)
```

* Если проект `example` установлен по нестандартному пути `/path/to/example`, его можно указать в переменной
окружения `CMAKE_PREFIX_PATH`:
```sh
$ export CMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH:/path/to/example
```

## Экспорты для сторонних библиотек {#cmake-external-export}

```cmake
# Файл cmake/FindFuse.cmake
find_path(FUSE_INC fuse3/fuse.h)
find_library(FUSE_LIBS fuse3)

add_library(Fuse::fuse3 INTERFACE IMPORTED)
set_target_properties(Fuse::fuse3 PROPERTIES
    INTERFACE_LINK_LIBRARIES ${FUSE_LIBS}
    INTERFACE_INCLUDE_DIRECTORIES ${FUSE_INC}
)
```

<div style="text-align:left">Использование</div>
```cmake
list(APPNED CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
#list(APPEND CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH})

find_package(Fuse REQUIRED)
target_link_libraries(myprog PUBLIC Fuse::fuse3)
```

---

# Подкаталоги {#cmake-subdirectory}

* `add_subdirectory` --- добавление каталога, в котором есть `CMakeLists.txt`
* Таргеты из других каталогов всегда read-only
* `install` можно сделать только в той же директории, где находится таргет

```cmake
cmake_minimum_required(VERSION 3.9)
project(example CXX)

file(GLOB SRCS src/*cpp)
add_library(unit ${SRCS})
add_subdirectory(tests)
```

```cmake
# tests/CMakeLists.txt
add_executable(testengine main.cpp)

add_test(first testengine -i one)
add_test(second testengine -i two)
add_test(third testengine -i three)
```

---

# Тесты {#cmake-ctest}

* Добавление теста `add_test(NAME name COMMAND cmd args)`
* Добавление параметров тестирования `set_tests_properties`
    * возможности test suite (`FIXTURES_SETUP/REQUIRED/CLEANUP`)
    * установка переменных окружения (`ENVIRONMENT`)
* Успешность теста --- возвращаемое значение команды
* Аналог команды `expect` из linux
