cmake_minimum_required(VERSION 3.9)
project(master-programming VERSION 0.1.0 LANGUAGES NONE
    DESCRIPTION "A source code for the course Master computer programming"
)

find_package(docproc REQUIRED COMPONENTS plantuml)

set(REVEALJS "https://rawgit.com/hakimel/reveal.js/master")

foreach(num RANGE 1 10)
    set(lecture lecture-${num})
    list(APPEND lectures ${lecture})
    file(GLOB ${lecture}_IMGS ${lecture}/uml/*.uml)
    file(GLOB ${lecture}_SRCS ${lecture}/*.md)
    file(GLOB RST ${lecture}/*.rst)
    set_property(SOURCE ${RST} PROPERTY COMPILE_OPTIONS -f rst+smart -s)
    list(APPEND ${lecture}_SRCS ${RST})
endforeach()

add_library(metadata metadata.yml)

foreach(lecture ${lectures})
    add_html(${lecture} ${${lecture}_SRCS})
    target_link_libraries(${lecture} PUBLIC metadata "-V revealjs-url=${REVEALJS}" "-t revealjs" "-F multifilter")
    if(${lecture}_IMGS)
        convert_image_for(TARGET ${lecture} FORMAT svg FILES ${${lecture}_IMGS} OPTIONS PLANTUML -SdefaultFontSize=20)
    endif()
endforeach()

set(INDEX_FILE ${CMAKE_CURRENT_BINARY_DIR}/index.md)
file(READ README.md README_CONTENT)
string(REGEX REPLACE "(lecture-[0-9]+)\\.(md|rst)" "\\1.html" README_CONTENT ${README_CONTENT})
file(GENERATE OUTPUT ${INDEX_FILE} CONTENT ${README_CONTENT})

add_html(index ${INDEX_FILE})
add_html(nixos-setup nixos-setup.md)

configure_file(GitHub.css GitHub.css COPYONLY)
