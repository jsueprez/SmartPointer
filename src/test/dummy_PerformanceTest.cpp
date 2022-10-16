#include "benchmark/benchmark.h"
#include "dummyLib.h"

static void BM_dummySum(benchmark::State &state)
{
  DummyLib object;
  int i1 = 2;
  int i2 = 3;

  // Perform setup here
  for (auto _ : state)
  {
    // This code gets timed
    object.dummySum(i1, i2);
  }
}
BENCHMARK(BM_dummySum);
