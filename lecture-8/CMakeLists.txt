add_html(lecture-8 index-part1.rst index-part2.rst index-part3.rst index-part4.rst)

target_compile_options(lecture-8 PUBLIC -f rst+smart)
set_source_files_properties(index-part1.rst PROPERTIES COMPILE_OPTIONS -s)
target_link_libraries(lecture-8 PUBLIC metadata ${SLIDY_OUTPUT})

file(GLOB UMLS uml/*.uml)
convert_image_for(TARGET lecture-8 FILES ${UMLS} FORMAT svg OPTIONS PLANTUML "-SdefaultFontSize=20")
