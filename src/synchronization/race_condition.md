# `race_condition.c` — an intentionally unsafe shared counter

Four threads repeatedly increment the same `counter` without coordinating
their updates. This is a **data race**: the final value is not reliable and
the program's behavior is not defined by the OpenMP/C rules.

This example is useful for understanding why simultaneous writes to shared
data need synchronization. Do not treat the displayed result as a guaranteed
value; compare it with `critical_demo.c` to see a protected update.

Build and run it using the command in the [examples guide](../README.md).
