find_package(Catch2 REQUIRED)
include(Catch)

add_executable(imgproc_test main.cpp imgproc.cpp)
target_link_libraries(imgproc_test Catch2::Catch2 imgproc)
catch_discover_tests(imgproc_test)

add_test(NAME test_help COMMAND imgproc_exe -h)
set_tests_properties(test_help PROPERTIES PASS_REGULAR_EXPRESSION ".*Usage:.*--help")

add_test(NAME test_no_args COMMAND imgproc_exe)
set_tests_properties(test_no_args PROPERTIES WILL_FAIL TRUE FAIL_REGULAR_EXPRESSION "I need 2 images.*")
