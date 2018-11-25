cmake_minimum_required(VERSION 3.9)
project(master-programming VERSION 0.1.0 LANGUAGES NONE
    DESCRIPTION "A source code for the course Master computer programming"
)

find_package(docproc REQUIRED COMPONENTS plantuml dot)
find_program(PANDOC_PIPE pandoc-pipe)

add_library(metadata metadata.yml)

set(SLIDY_OUTPUT "-t slidy" --template=${CMAKE_SOURCE_DIR}/templates/slidy.thtml)
set(REVEALJS_OUTPUT "-t revealjs" --template=${CMAKE_SOURCE_DIR}/templates/revealjs.thtml)

add_subdirectory(lecture-1)
add_subdirectory(lecture-2)
add_subdirectory(lecture-3)
add_subdirectory(lecture-4)
add_subdirectory(lecture-5)
add_subdirectory(lecture-6)
add_subdirectory(lecture-7)
add_subdirectory(lecture-8)
add_subdirectory(lecture-9)
add_subdirectory(lecture-10)
add_subdirectory(lecture-11)

set(INDEX_FILE ${CMAKE_CURRENT_BINARY_DIR}/index.rst)
file(READ README.rst README_CONTENT)
string(REGEX REPLACE "(lecture-[0-9]+)/index\\.rst" "\\1.html" README_CONTENT ${README_CONTENT})
file(GENERATE OUTPUT ${INDEX_FILE} CONTENT ${README_CONTENT})

add_html(index ${INDEX_FILE})
target_link_libraries(index "-M title:'Master Programming'")
add_html(nixos-setup nixos-setup.md)
