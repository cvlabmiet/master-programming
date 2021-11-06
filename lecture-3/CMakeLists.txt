file(GLOB IMGS images/*.dot)
add_asciidoc(lecture-3 index.adoc DEPENDS ${IMGS})
