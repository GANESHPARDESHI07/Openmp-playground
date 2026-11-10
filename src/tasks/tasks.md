# `tasks.c` — running independent tasks

Inside a parallel region, one thread creates three OpenMP tasks. They
represent preprocessing, feature extraction, and model evaluation. The tasks
can run on available threads, and `taskwait` makes the creating thread wait
until all three are finished.

This example introduces tasks for work that is not naturally expressed as a
loop. The order of task messages and the thread numbers can vary.

Build and run it using the command in the [examples guide](../README.md).
