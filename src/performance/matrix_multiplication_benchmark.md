# `matrix_multiplication_benchmark.c` — comparing matrix multiplication

This program creates two 1000-by-1000 matrices, multiplies them sequentially,
then repeats the multiplication with an OpenMP `parallel for`. It compares the
results and reports elapsed time and speedup.

It helps show how a loop with independent output rows can be parallelized and
how to check that the parallel result matches the sequential result. Timing
depends on the computer and may not show a speedup for every setup. The
program appends measurements to `results/sequential_results.txt`. Its final
console message names a different file, but the code writes to that
`sequential_results.txt` path.

Build and run it using the command in the [examples guide](../README.md).
