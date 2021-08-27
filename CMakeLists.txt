cmake_minimum_required(VERSION 3.14)
project(bud)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY     https://github.com/google/googletest.git
  GIT_TAG            release-1.11.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(hello_test test/hello_test.cc)
target_link_libraries(hello_test gtest_main)
