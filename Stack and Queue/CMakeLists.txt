cmake_minimum_required(VERSION 3.14)
project(data_structs_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(all_tests test_structures.cpp)

target_include_directories(all_tests PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(all_tests PRIVATE 
    GTest::gtest_main
)

target_compile_definitions(all_tests PRIVATE GTEST_COLOR=1)

add_test(NAME all_tests COMMAND all_tests --gtest_color=yes)