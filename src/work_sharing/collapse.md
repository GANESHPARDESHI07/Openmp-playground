# `collapse.c` — parallelizing nested loops

This program multiplies matrices in two ways. Both versions use OpenMP, but
the second adds `collapse(2)` so OpenMP treats the two outer loops as one
larger iteration space.

The example helps show how loop collapsing can expose more independent work
when one loop by itself does not provide enough iterations. It checks that
both results match and compares their average run times.

Build and run it using the command in the [examples guide](../README.md).
