file(GLOB IMGS diagrams/*.dot)
add_library(diagrams OBJECT ${IMGS})

add_html(lecture-9 index.rst)
target_compile_options(lecture-9 PUBLIC -s)
set_source_files_properties(index.rst PROPERTIES COMPILE_OPTIONS "-f;rst+smart")
target_link_libraries(lecture-9 PUBLIC metadata diagrams ${SLIDY_OUTPUT})
