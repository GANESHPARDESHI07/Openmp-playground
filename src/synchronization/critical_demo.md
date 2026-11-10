# `critical_demo.c` — protecting shared updates

Four threads each add `2` to `total` and increment `count` 100,000 times.
OpenMP's `critical` region allows only one thread at a time to perform those
updates, so the expected totals are `800000` and `400000`.

This example shows how a critical region can prevent lost updates in shared
data. It also shows why putting a frequently repeated operation in a critical
region can limit parallel performance.

Build and run it using the command in the [examples guide](../README.md).
