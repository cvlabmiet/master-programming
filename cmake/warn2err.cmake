math(EXPR __last "${CMAKE_ARGC} - 1")
set(__is_next FALSE)
foreach(__i RANGE ${__last})
    if(__is_next)
        foreach(__x RANGE ${__i} ${__last})
            list(APPEND __args "${CMAKE_ARGV${__x}}")
        endforeach()
        break()
    endif()

    if(CMAKE_ARGV${__i} STREQUAL "--")
        set(__is_next TRUE)
    endif()
endforeach()

execute_process(
    COMMAND ${__args}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    ECHO_OUTPUT_VARIABLE
    ECHO_ERROR_VARIABLE
    ERROR_VARIABLE __output
    COMMAND_ERROR_IS_FATAL ANY
)

string(FIND "${__output}" "asciidoc: WARNING:" __loc)
if(NOT __loc EQUAL -1)
    message(FATAL_ERROR "WARNING treated as ERROR")
endif()
