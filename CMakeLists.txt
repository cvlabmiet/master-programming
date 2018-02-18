cmake_minimum_required(VERSION 3.9)
project(master-programming VERSION 0.1.0 LANGUAGES NONE
    DESCRIPTION "A source code for the course Master computer programming"
)

include(ExternalProject)

find_program(PANDOC pandoc)
if(NOT PANDOC)
    message(SEND_ERROR "pandoc has not been found")
endif()

file(GLOB SOURCES *.md)
set(METADATA ${CMAKE_SOURCE_DIR}/metadata.yml)

foreach(SRC ${SOURCES})
    get_filename_component(SRC_WE ${SRC} NAME_WE)
    set(OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/${SRC_WE}.html)
    add_custom_command(OUTPUT ${OUTPUT_FILE}
        COMMAND ${PANDOC} -f markdown+raw_tex -s -t revealjs --section-divs ${METADATA} ${SRC} -o ${OUTPUT_FILE}
        DEPENDS ${SRC} ${METADATA}
    )
    list(APPEND OUTPUTS ${OUTPUT_FILE})
endforeach()

add_custom_target(document ALL DEPENDS ${OUTPUTS})

ExternalProject_Add(revealjs
    GIT_REPOSITORY https://github.com/hakimel/reveal.js.git
    GIT_TAG 3.6.0
    GIT_SHALLOW TRUE
    GIT_PROGRESS FALSE

    SOURCE_DIR ${CMAKE_BINARY_DIR}/reveal.js

    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""

    INSTALL_COMMAND ""
)
