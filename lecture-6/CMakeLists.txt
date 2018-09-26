add_html(lecture-6 index.rst)
target_compile_options(lecture-6 PUBLIC -f rst+smart -s -F ${PANDOC_PIPE})
target_link_libraries(lecture-6 PUBLIC metadata "-t slidy" "--self-contained" "--template=${SLIDY_TEMPLATE}")
