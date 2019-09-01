add_library(lecture-9-images OBJECT images/rule.dot)

add_html(lecture-9 index.rst)
target_compile_options(lecture-9 PUBLIC -f rst+smart -s)
target_link_libraries(lecture-9 PUBLIC metadata lecture-9-images ${SLIDY_OUTPUT})
