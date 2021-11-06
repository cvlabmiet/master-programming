file(GLOB OTHER_SRCS *.adoc images/*.dot images/*.uml)
add_asciidoc(lecture-10 index.adoc DEPENDS ${OTHER_SRCS})
