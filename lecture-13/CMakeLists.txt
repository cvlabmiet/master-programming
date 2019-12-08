add_html(lecture-13 index.rst)
target_compile_options(lecture-13 PUBLIC -f rst+smart -s)
target_link_libraries(lecture-13 PUBLIC metadata ${SLIDY_OUTPUT})
