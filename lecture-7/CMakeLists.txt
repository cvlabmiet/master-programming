add_html(lecture-7 index.rst)
target_compile_options(lecture-7 PUBLIC -f rst+smart -s -F ${PANDOC_PIPE})
target_link_libraries(lecture-7 PUBLIC metadata "-t slidy" "--self-contained" "--template=${SLIDY_TEMPLATE}")
