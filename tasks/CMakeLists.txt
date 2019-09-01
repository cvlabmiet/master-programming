add_html(tasks index.rst)
target_compile_options(tasks PUBLIC -f rst+smart -s)
target_link_libraries(tasks metadata --resource-path=${CMAKE_CURRENT_SOURCE_DIR}/images ${SLIDY_OUTPUT} --self-contained)
