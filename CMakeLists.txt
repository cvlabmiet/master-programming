cmake_minimum_required(VERSION 3.19)
project(master-programming VERSION 0.1.0 LANGUAGES CXX
    DESCRIPTION "A source code for the course Master computer programming"
)

set(CMAKE_CXX_STANDARD 20)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wpedantic\;-Werror\;-Wall\;-Wextra>)

find_program(ASCIIDOC asciidoc REQUIRED)
find_program(DOT dot REQUIRED)
find_program(PLANTUML plantuml REQUIRED)

find_package(Boost REQUIRED COMPONENTS timer chrono thread mpi coroutine serialization program_options log_setup log)

function(add_asciidoc __target __files)
    cmake_parse_arguments(__prefix "" "" "DEPENDS" ${ARGN})
    set(__abs_files)
    foreach(__file ${__files})
        get_filename_component(__file ${__file} ABSOLUTE)
        list(APPEND __abs_files ${__file})
    endforeach()

    add_custom_command(OUTPUT index.html
        COMMAND ${ASCIIDOC} -o ${CMAKE_CURRENT_BINARY_DIR}/index.html
            --backend ${CMAKE_SOURCE_DIR}/templates/slidy-custom
            -a stylesheet=${CMAKE_SOURCE_DIR}/templates/slidy-custom.css
            ${__abs_files}
        DEPENDS ${__files}
            ${CMAKE_SOURCE_DIR}/templates/slidy-custom.conf
            ${CMAKE_SOURCE_DIR}/templates/slidy-custom.css
            ${__prefix_DEPENDS}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    add_custom_target(${__target} ALL DEPENDS index.html)
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

add_custom_command(OUTPUT index.html
    COMMAND ${ASCIIDOC} -o ${CMAKE_CURRENT_BINARY_DIR}/index.html
        --backend html5 -a env-html=1
        ${CMAKE_SOURCE_DIR}/README.adoc
    DEPENDS README.adoc)
add_custom_target(main ALL DEPENDS index.html)
