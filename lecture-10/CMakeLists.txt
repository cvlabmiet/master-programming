file(GLOB UMLS images/*.uml)
add_library(lecture-10-images OBJECT ${UMLS})
target_compile_options(lecture-10-images PRIVATE -SdefaultFontSize=20)

set_source_files_properties(index-part1.rst PROPERTIES COMPILE_OPTIONS -s)

add_html(lecture-10 index-part1.rst index-part2.rst index-part3.rst index-part4.rst)
target_compile_options(lecture-10 PUBLIC -f rst+smart)
target_link_libraries(lecture-10 metadata lecture-10-images ${SLIDY_OUTPUT})
