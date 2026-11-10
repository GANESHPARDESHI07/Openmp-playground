# `section.c` — sharing separate jobs

The program creates three threads and defines three independent sections:
matrix multiplication, data preprocessing, and model evaluation. OpenMP
assigns each section to one thread; the assignment is not fixed.

This is useful when a program has a small number of different jobs rather than
many repetitions of the same loop. The final message appears after all
sections finish.

Build and run it using the command in the [examples guide](../README.md).
