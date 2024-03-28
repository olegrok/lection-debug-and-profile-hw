#include <benchmark/benchmark.h>
#include "stack.h"

static void BM_Push(benchmark::State& state) {
    Stack stack;
    initStack(&stack);
    for (auto _ : state) {
        push(&stack, 10);
    }
}
BENCHMARK(BM_Push);

static void BM_Pop(benchmark::State& state) {
    Stack stack;
    initStack(&stack);

    push(&stack, 10);
    for (auto _ : state) {
        pop(&stack);
    }
}
BENCHMARK(BM_Pop);

BENCHMARK_MAIN();
