#include "benchmark/benchmark.h"
#include "dummyLib.h"

#include "dynamicArray.h"

// Return a copy of arr with all of the values doubled
DynamicArray<int> cloneArrayAndDouble(const DynamicArray<int> &arr) {
  DynamicArray<int> dbl(arr.getLength());
  for (auto i{0}; i < arr.getLength(); i++) {
    dbl[i] = arr[i] * 2;
  }
  return dbl;
}

// Return a copy of arr with all of the values doubled
DynamicArray_2<int> cloneArrayAndDouble_2(const DynamicArray_2<int> &arr) {
  DynamicArray_2<int> dbl(arr.getLength());
  for (auto i{0}; i < arr.getLength(); i++) {
    dbl[i] = arr[i] * 2;
  }
  return dbl;
}

static void BM_DynamicArray_CopySemantics(benchmark::State &state) {

  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
    DynamicArray<int> arr(1000000);
    for (auto i{0}; i < arr.getLength(); i++) {
      arr[i] = i;
    }

    arr = cloneArrayAndDouble(arr);
  }
}
BENCHMARK(BM_DynamicArray_CopySemantics);

static void BM_DynamicArray_MoveSemantics(benchmark::State &state) {

  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
    DynamicArray_2<int> arr(1000000);
    for (auto i{0}; i < arr.getLength(); i++) {
      arr[i] = i;
    }

    arr = cloneArrayAndDouble_2(arr);
  }
}
BENCHMARK(BM_DynamicArray_MoveSemantics);
