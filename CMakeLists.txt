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

include_directories(${PROJECT_SOURCE_DIR}/include)

enable_testing()

include(GoogleTest)

AUX_SOURCE_DIRECTORY(test all_test_file)
add_executable(all_tests ${all_test_file})
target_link_libraries(all_tests gtest_main gmock_main)

gtest_discover_tests(all_tests)
