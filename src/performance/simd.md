# `simd.c` — vectorizing a loop

This program adds two arrays in a regular loop and then repeats the operation
with OpenMP's `simd` directive. SIMD lets a processor apply one instruction to
multiple data values at once when supported by the compiler and hardware.

The program compares timings and checks that both methods produced the same
values. Compiler optimizations may already vectorize the regular loop, so the
measured speedup can vary or may not appear.

Build and run it using the command in the [examples guide](../README.md).
