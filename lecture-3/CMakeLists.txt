add_html(lecture-3 index.rst)
target_compile_options(lecture-3 PUBLIC -f rst+smart -s)
target_link_libraries(lecture-3 PUBLIC metadata "-t slidy" "--self-contained" "--template=${SLIDY_TEMPLATE}")
convert_image_for(TARGET lecture-3 FORMAT svg FILES library.dot)
