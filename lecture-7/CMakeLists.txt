add_library(lecture-7-images OBJECT images/ref.dot)

add_html(lecture-7 index.rst)
target_compile_options(lecture-7 PUBLIC -f rst+smart -s)
target_link_libraries(lecture-7 PUBLIC metadata lecture-7-images ${SLIDY_OUTPUT})
