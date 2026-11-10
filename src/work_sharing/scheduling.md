# `scheduling.c` — scheduling loop iterations

The `parallel for` directive shares 30 loop iterations among OpenMP threads.
The `guided` schedule starts with larger groups of iterations and gives out
smaller groups as work remains. Each message identifies the thread handling
that iteration.

This is useful for observing how OpenMP divides loop work. The order of
messages and which thread handles a given iteration can vary between runs.

Build and run it using the command in the [examples guide](../README.md).
