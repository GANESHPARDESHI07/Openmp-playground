# OpenMP examples

These examples are grouped by the OpenMP idea they demonstrate. Each C file
has a companion Markdown guide with a plain-language explanation.

## Topics

- **Basics:** [first parallel region](basics/first_openmp.md),
  [shared and private data](basics/data_sharing.md), and
  [nested parallelism](basics/nested_parallelism.md).
- **Synchronization:** [race conditions](synchronization/race_condition.md)
  and [critical regions](synchronization/critical_demo.md).
- **Work sharing:** [loop scheduling](work_sharing/scheduling.md),
  [independent sections](work_sharing/section.md), and
  [collapsing nested loops](work_sharing/collapse.md).
- **Tasks:** [independent tasks](tasks/tasks.md) and
  [task dependencies](tasks/task_dependency.md).
- **Performance:** [parallel reduction](performance/reduction_demo.md),
  [matrix multiplication](performance/matrix_multiplication_benchmark.md)
  and [an alternate matrix benchmark](performance/matrix_multiplication_benchmark_variant.md),
  [cache-aware loop ordering](performance/cache_benchmark.md),
  [cache blocking](performance/cache_blocking.md),
  [false sharing](performance/false_sharing.md), and
  [SIMD vectorization](performance/simd.md).

## Build and run an example

Install a C compiler with OpenMP support, such as GCC. From the project root,
compile one example with `-fopenmp`, then run the resulting program. For
example:

```sh
mkdir -p build
gcc -Wall -Wextra -fopenmp src/basics/first_openmp.c -o build/first_openmp
./build/first_openmp
```

Replace the source path and output name to try another example. Some
performance examples append measurements to `results/sequential_results.txt`,
so run them from the project root where the `results` directory is available.
Their timings depend on your computer and should be treated as demonstrations,
not universal benchmarks.
