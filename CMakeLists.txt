cmake_minimum_required(VERSION 3.9)
project(master-programming VERSION 0.1.0 LANGUAGES NONE
    DESCRIPTION "A source code for the course Master computer programming"
)

option(USE_LOCAL_REVEALJS "Download revealjs for local use" OFF)

include(ExternalProject)

find_program(PANDOC pandoc)
if(NOT PANDOC)
    message(SEND_ERROR "pandoc has not been found")
endif()

set(FORMAT "markdown+raw_tex+bracketed_spans")

file(GLOB SOURCES *.md)
list(FILTER SOURCES EXCLUDE REGEX README.md)
set(METADATA ${CMAKE_SOURCE_DIR}/metadata.yml)
if(NOT USE_LOCAL_REVEALJS)
    set(REVELJS_URL -V "revealjs-url=https://rawgit.com/hakimel/reveal.js/master")
endif()

foreach(SRC ${SOURCES})
    get_filename_component(SRC_WE ${SRC} NAME_WE)
    set(OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/${SRC_WE}.html)
    add_custom_command(OUTPUT ${OUTPUT_FILE}
        COMMAND ${PANDOC} -f ${FORMAT} ${REVELJS_URL} -s -t revealjs --section-divs ${METADATA} ${SRC} -o ${OUTPUT_FILE}
        DEPENDS ${SRC} ${METADATA}
    )
    list(APPEND OUTPUTS ${OUTPUT_FILE})
endforeach()

set(OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/index.html)
set(README_FILE ${CMAKE_CURRENT_BINARY_DIR}/README.md)
file(READ README.md README_CONTENT)
string(REGEX REPLACE "(lecture-[0-9]+)\.md" "\\1.html" README_CONTENT ${README_CONTENT})
file(GENERATE OUTPUT ${README_FILE} CONTENT ${README_CONTENT})
add_custom_command(OUTPUT ${OUTPUT_FILE}
    COMMAND ${PANDOC} -V pagetitle=${PROJECT_NAME} -f ${FORMAT} -s -t html5 ${README_FILE} -o ${OUTPUT_FILE}
    DEPENDS ${README_FILE}
)
list(APPEND OUTPUTS ${OUTPUT_FILE})

add_custom_target(document ALL DEPENDS ${OUTPUTS})

if(USE_LOCAL_REVEALJS)
    ExternalProject_Add(revealjs
        GIT_REPOSITORY https://github.com/hakimel/reveal.js.git
        GIT_TAG 3.6.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS FALSE
        SOURCE_DIR ${CMAKE_BINARY_DIR}/reveal.js
        CONFIGURE_COMMAND "" BUILD_COMMAND "" INSTALL_COMMAND ""
    )
endif()
