# `nested_parallelism.c` — parallel regions inside parallel regions

This program starts an outer team of two threads. Each outer thread then
starts an inner parallel region, illustrating nested parallelism. It prints
the thread number, team size, and nesting level so you can see which region
each thread belongs to.

Nested teams are subject to OpenMP runtime settings and hardware limits, so
the exact output can vary.

Build and run it using the command in the [examples guide](../README.md).
