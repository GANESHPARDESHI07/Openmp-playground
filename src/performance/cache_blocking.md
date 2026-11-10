# `cache_blocking.c` — processing matrices in blocks

This program compares two sequential matrix multiplication approaches: one
processes the full matrices directly, and the other divides the work into
smaller blocks. It checks that both approaches produce the same result and
compares their average run times.

Blocking can improve data reuse in the processor's cache, but the best block
size depends on the computer and compiler. This example focuses on cache
behavior; its blocked implementation is not itself parallel.

Build and run it using the command in the [examples guide](../README.md).
