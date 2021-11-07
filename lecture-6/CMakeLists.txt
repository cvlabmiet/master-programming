file(GLOB IMGS images/*.dot)
add_asciidoc(lecture-6 index.adoc DEPENDS ${IMGS})
