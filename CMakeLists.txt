cmake_minimum_required(VERSION 3.14)
project(bud)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY     https://github.com/google/googletest.git
  GIT_TAG            release-1.11.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(${PROJECT_SOURCE_DIR}/src)

enable_testing()

add_executable(hello_test test/hello.cc)
target_link_libraries(hello_test gtest_main)

add_executable(timer_test test/timer.cc)
target_link_libraries(timer_test gtest_main)

include(GoogleTest)
gtest_discover_tests(hello_test)
gtest_discover_tests(timer_test)