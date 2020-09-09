add_html(lecture-1 index.rst)
target_compile_options(lecture-1 PUBLIC -f rst+smart -s)
target_link_libraries(lecture-1 PUBLIC metadata ${SLIDY_OUTPUT})
