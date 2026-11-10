# `reduction_demo.c` — safely adding values in parallel

The program fills a large array with `1`, sums it sequentially, then sums it
in parallel using OpenMP's `reduction(+:parallel_sum)`. Each thread can add to
its own temporary sum; OpenMP combines those sums at the end. The two sums
should match.

It demonstrates a common way to calculate a total without having every thread
compete to update one shared variable. It also measures and prints the
sequential and parallel times and speedup. Timing results vary by computer;
the program appends results to `results/sequential_results.txt`.

Build and run it using the command in the [examples guide](../README.md).
