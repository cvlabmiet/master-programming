add_library(lecture-8-images OBJECT images/rule.dot)

add_html(lecture-8 index.rst)
target_compile_options(lecture-8 PUBLIC -f rst+smart -s)
target_link_libraries(lecture-8 PUBLIC metadata lecture-8-images ${SLIDY_OUTPUT})
