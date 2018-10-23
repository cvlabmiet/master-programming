add_html(lecture-2 index.rst)
target_compile_options(lecture-2 PUBLIC -f rst+smart -s)
target_link_libraries(lecture-2 PUBLIC metadata ${REVEALJS_OUTPUT})
