add_html(lecture-11 index.rst)
target_compile_options(lecture-11 PUBLIC -f rst+smart -s)
target_link_libraries(lecture-11 PUBLIC metadata ${SLIDY_OUTPUT})
