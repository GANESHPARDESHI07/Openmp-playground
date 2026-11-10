# `matrix_multiplication_benchmark_variant.c` — another matrix benchmark copy

This is a second version of the matrix multiplication benchmark. Like
`matrix_multiplication_benchmark.c`, it compares sequential and
OpenMP-parallel multiplication for 1000-by-1000 matrices, checks the results,
and reports timings and speedup. It differs mainly in its final console
message.

It is kept as a separate example so the existing source is preserved, but
most learners only need to study one of the two versions. It appends results
to `results/sequential_results.txt`.

Build and run it using the command in the [examples guide](../README.md).
