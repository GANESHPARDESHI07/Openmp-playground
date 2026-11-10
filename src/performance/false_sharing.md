# `false_sharing.c` — adjacent counters and cache lines

Four threads repeatedly update separate counters stored next to one another,
then repeat with counters spaced apart. Although the counters are independent,
nearby values can occupy the same cache line and cause cache-coherence traffic,
a performance problem called **false sharing**.

This program compares elapsed times to make that effect visible. Results vary
with hardware and system load; timings are not guaranteed to show a specific
improvement.

Build and run it using the command in the [examples guide](../README.md).
