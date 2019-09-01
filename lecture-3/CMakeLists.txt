add_library(lecture-3-images OBJECT images/library.dot)

add_html(lecture-3 index.rst)
target_compile_options(lecture-3 PUBLIC -f rst+smart -s)
target_link_libraries(lecture-3 metadata lecture-3-images ${SLIDY_OUTPUT})
