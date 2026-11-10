# `task_dependency.c` — ordering tasks with dependencies

Three tasks form a small workflow: Task A writes `data`, Task B reads `data`
and writes `processed`, and Task C reads `processed`. The `depend` clauses
tell OpenMP which tasks must wait for earlier tasks before using those values.
The final `taskwait` waits for the workflow to finish.

This is helpful for learning how to express prerequisites between tasks while
still allowing unrelated work to run in parallel.

Build and run it using the command in the [examples guide](../README.md).
