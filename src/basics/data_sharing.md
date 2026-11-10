# `data_sharing.c` — shared and private variables

This example makes `shared_value` visible to all four threads, while
`private_value` gets a separate copy for each thread. Each thread sets and
prints its own private copy. After the parallel region, the original
`private_value` is still `-1`, while `shared_value` is still `100`.

It helps explain the difference between data that threads share and data that
each thread owns. The order of the thread messages is not fixed.

Build and run it using the command in the [examples guide](../README.md).
