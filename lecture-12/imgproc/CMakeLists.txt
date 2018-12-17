cmake_minimum_required(VERSION 3.12)
project(imgproc VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "Image processing program")

include(CMakePackageConfigHelpers)
include(CTest)
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wall\;-Werror\;-pedantic\;-Wextra>)
if(COVERAGE)
    configure_file(CTestCustom.cmake CTestCustom.cmake COPYONLY)
    add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-ftest-coverage>)
    list(APPEND CMAKE_CXX_FLAGS -fprofile-arcs)
endif()

find_package(Boost REQUIRED)
find_package(PNG REQUIRED)
find_package(JPEG REQUIRED)
find_package(cxxopts REQUIRED)

configure_file(imgproc-version.hpp.in imgproc-version.hpp @ONLY)

add_library(imgproc INTERFACE)
target_include_directories(imgproc INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include\;${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/include>
)
target_link_libraries(imgproc INTERFACE Boost::boost)
install(TARGETS imgproc EXPORT imgproc-targets)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/imgproc-version.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_executable(imgproc_exe src/main.cpp)
target_link_libraries(imgproc_exe imgproc PNG::PNG JPEG::JPEG cxxopts::cxxopts)
set_target_properties(imgproc_exe PROPERTIES OUTPUT_NAME imgproc)
install(TARGETS imgproc_exe EXPORT imgproc-targets RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

export(TARGETS imgproc imgproc_exe FILE imgproc-targets.cmake)
configure_package_config_file(imgproc-config.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/imgproc-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}
)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/imgproc-config-version.cmake
    COMPATIBILITY SameMajorVersion
)

install(EXPORT imgproc-targets DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/imgproc-config.cmake ${CMAKE_CURRENT_BINARY_DIR}/imgproc-config-version.cmake
    DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}
)
install(DIRECTORY tests/ DESTINATION ${CMAKE_INSTALL_DOCDIR})
install(FILES README.rst DESTINATION ${CMAKE_INSTALL_DOCDIR})

list(APPEND CPACK_GENERATOR TGZ)
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_SYSTEM_NAME ${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR})
set(CPACK_PACKAGE_CONTACT "MIET")
include(CPack)
