file(GLOB UMLS uml/*.uml)
add_library(umls OBJECT ${UMLS})
target_compile_options(umls PRIVATE -SdefaultFontSize=20)

set_source_files_properties(index-part1.rst PROPERTIES COMPILE_OPTIONS -s)

add_html(lecture-8 index-part1.rst index-part2.rst index-part3.rst index-part4.rst)
target_compile_options(lecture-8 PUBLIC -f rst+smart)
target_link_libraries(lecture-8 metadata umls ${SLIDY_OUTPUT})
