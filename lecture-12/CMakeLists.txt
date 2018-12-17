add_html(lecture-12 index.rst)
target_compile_options(lecture-12 PUBLIC -f rst+smart -s)
target_link_libraries(lecture-12 PUBLIC metadata ${SLIDY_OUTPUT})
