file(GLOB SRCS *.cpp)
foreach(__src ${SRCS})
    get_filename_component(__name ${__src} NAME_WE)
    add_executable(${__name} ${__src})
    list(APPEND __exe ${__name})
endforeach()

add_asciidoc(lecture-8 index.adoc DEPENDS ${__exe})
