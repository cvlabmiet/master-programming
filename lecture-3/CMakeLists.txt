add_library(images OBJECT library.dot)

add_html(lecture-3 index.rst)
target_compile_options(lecture-3 PUBLIC -f rst+smart -s)
target_link_libraries(lecture-3 metadata images ${SLIDY_OUTPUT})
