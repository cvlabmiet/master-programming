add_html(lecture-5 index.rst)
target_compile_options(lecture-5 PUBLIC -f rst+smart -s)
target_link_libraries(lecture-5 PUBLIC metadata "-t slidy" "--self-contained" "--template=${SLIDY_TEMPLATE}")
