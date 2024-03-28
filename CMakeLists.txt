cmake_minimum_required(VERSION 3.10)
project(StackExample)

find_package(Threads REQUIRED)

# Enable C11 standard
set(CMAKE_C_STANDARD 11)

# Add ASAN, UBSAN, TSAN flags
if(ENABLE_ASAN)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
    set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
endif()

if(ENABLE_UBSAN)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=undefined")
    set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined")
endif()

if(ENABLE_TSAN)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=thread")
    set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=thread")
endif()

# Add source files
add_library(stack src/stack.c src/stack.h)
target_include_directories(stack PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(example src/main.c)
target_link_libraries(example stack)

# Add Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Add tests
enable_testing()
add_executable(tests test/test_stack.cpp)
target_link_libraries(tests gtest_main stack)

if(ENABLE_GCOV)
    target_compile_options(tests PRIVATE "--coverage")
    target_link_options(tests PRIVATE "--coverage")
endif()

add_test(NAME tests COMMAND tests)

# Add Google Benchmark
FetchContent_Declare(
    googlebenchmark
    URL https://github.com/google/benchmark/archive/refs/tags/v1.8.3.zip
)
FetchContent_MakeAvailable(googlebenchmark)

# Add benchmarks
add_executable(benchmarks benchmarks/benchmark_stack.cpp)
target_link_libraries(benchmarks benchmark::benchmark stack)

# Add cppcheck and clang-tidy targets
find_program(CPPCHECK cppcheck)
if(CPPCHECK)
    add_custom_target(
        cppcheck
        COMMAND ${CPPCHECK} --enable=all --suppress=missingIncludeSystem --quiet ${CMAKE_SOURCE_DIR}/src
    )
endif()

find_program(CLANGTIDY clang-tidy)
if(CLANGTIDY)
    add_custom_target(
        clang-tidy
        COMMAND ${CLANGTIDY} -p ${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR}/src/*.c ${CMAKE_SOURCE_DIR}/src/*.h --
    )
endif()
