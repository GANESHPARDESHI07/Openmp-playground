# `first_openmp.c` — a first parallel region

This program starts four OpenMP threads. Each thread prints its number, and
then all threads meet at a **barrier** before thread 0 prints that everyone has
arrived.

It is a helpful first example for seeing how a parallel region works and how a
barrier makes threads wait for one another. The order of the thread messages
can change from run to run.

Build and run it using the command in the [examples guide](../README.md).
