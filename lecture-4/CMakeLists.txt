add_html(lecture-4 index.rst)
target_compile_options(lecture-4 PUBLIC -f rst+smart -s)
target_link_libraries(lecture-4 PUBLIC metadata "-t slidy" "--self-contained" "--template=${SLIDY_TEMPLATE}")
