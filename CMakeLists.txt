cmake_minimum_required(VERSION 3.9)
project(master-programming VERSION 0.1.0 LANGUAGES CXX
    DESCRIPTION "A source code for the course Master computer programming"
)

set(CMAKE_CXX_STANDARD 17)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wpedantic\;-Werror\;-Wall\;-Wextra>)

find_package(docproc REQUIRED COMPONENTS plantuml dot)

add_library(metadata metadata.yml)

set(SLIDY_OUTPUT "-t slidy" --template=${CMAKE_SOURCE_DIR}/templates/slidy.thtml)
set(REVEALJS_OUTPUT "-t revealjs" --template=${CMAKE_SOURCE_DIR}/templates/revealjs.thtml)

find_program(ASCIIDOC asciidoc REQUIRED)
function(add_asciidoc __target __files)
    cmake_parse_arguments(__prefix "" "" "DEPENDS" ${ARGN})
    set(__abs_files)
    foreach(__file ${__files})
        get_filename_component(__file ${__file} ABSOLUTE)
        list(APPEND __abs_files ${__file})
    endforeach()

    add_custom_command(OUTPUT ${__target}.html
        COMMAND ${ASCIIDOC} -o ${CMAKE_CURRENT_BINARY_DIR}/${__target}.html
            --backend ${CMAKE_SOURCE_DIR}/templates/slidy-custom
            -a stylesheet=${CMAKE_SOURCE_DIR}/templates/slidy-custom.css
            ${__abs_files}
        DEPENDS ${__files}
            ${CMAKE_SOURCE_DIR}/templates/slidy-custom.conf
            ${CMAKE_SOURCE_DIR}/templates/slidy-custom.css
            ${__prefix_DEPENDS}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    add_custom_target(${__target} ALL DEPENDS ${__target}.html)
endfunction()

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
add_subdirectory(lecture-12)
add_subdirectory(lecture-13)
add_subdirectory(tasks)

set(INDEX_FILE ${CMAKE_CURRENT_BINARY_DIR}/index.rst)
file(READ README.rst README_CONTENT)
string(REGEX REPLACE "(lecture-[0-9]+|tasks)/index\\.(rst|adoc)" "\\1.html" README_CONTENT ${README_CONTENT})
file(GENERATE OUTPUT ${INDEX_FILE} CONTENT ${README_CONTENT})

add_html(index ${INDEX_FILE})
target_link_libraries(index "-M title:'Master Programming'")
add_html(nixos-setup nixos-setup.md)
