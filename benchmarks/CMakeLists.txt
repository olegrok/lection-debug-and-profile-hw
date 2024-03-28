add_executable(benchmarks benchmark_stack.cpp stack.c stack.h)
target_link_libraries(benchmarks benchmark::benchmark)

