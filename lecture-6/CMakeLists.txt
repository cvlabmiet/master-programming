add_library(lecture-6-images OBJECT images/stl.uml)
target_compile_options(lecture-6-images PRIVATE -SdefaultFontSize=20)

add_html(lecture-6 index.rst)
target_compile_options(lecture-6 PUBLIC -f rst+smart -s)
target_link_libraries(lecture-6 PUBLIC metadata lecture-6-images ${SLIDY_OUTPUT})
