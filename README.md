# OpenMP Playground

A collection of small C programs for learning OpenMP, from creating threads
to comparing parallel performance. The source examples are organized by topic
in [`src/`](src/README.md), and each example has a short companion guide.

## Requirements

- GCC or another C compiler with OpenMP support
- A terminal and a system with an OpenMP runtime

## Build and run

From the project root, compile any example with `-fopenmp`. For example:

```sh
mkdir -p build
gcc -Wall -Wextra -fopenmp src/basics/first_openmp.c -o build/first_openmp
./build/first_openmp
```

See [`src/README.md`](src/README.md) for the topic index and a list of the
examples. `build/` and generated benchmark measurements are intentionally
ignored by Git.

## Notes

- Thread scheduling and printed output order may vary between runs.
- Benchmark timings depend on your compiler, machine, and system load; they
  are learning aids rather than universal performance claims.
- `src/synchronization/race_condition.c` intentionally demonstrates an unsafe
  data race. Its output is not reliable.
