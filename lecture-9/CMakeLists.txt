foreach(_i RANGE 1 17)
    list(APPEND SRCS index${_i}.rst)
endforeach()
set_source_files_properties(index.rst PROPERTIES COMPILE_OPTIONS -s)

add_html(lecture-9 index.rst ${SRCS})
target_compile_options(lecture-9 PUBLIC -f rst+smart)
target_link_libraries(lecture-9 PUBLIC metadata ${SLIDY_OUTPUT})
