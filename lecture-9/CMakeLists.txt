add_html(lecture-9 index.rst)
target_compile_options(lecture-9 PUBLIC -f rst+smart -s)
target_link_libraries(lecture-9 PUBLIC metadata ${SLIDY_OUTPUT})
