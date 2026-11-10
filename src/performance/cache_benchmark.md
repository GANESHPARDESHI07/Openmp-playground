# `cache_benchmark.c` — loop order and matrix performance

This program multiplies two matrices using an `i-k-j` loop order, once
sequentially and once with OpenMP distributing rows. It repeats each run,
checks that the answers match, and reports average time, speedup, and an
estimated parallel efficiency.

The example helps demonstrate how loop order and parallel work distribution
can affect performance. The measurements vary by machine and are not
guaranteed to show a speedup.

Build and run it using the command in the [examples guide](../README.md).
