
#include <stdio.h>
#include <omp.h>

#define THREADS 4
#define ITERATIONS 100000000

typedef struct {
    long long value;
} Counter;

typedef struct {
    _Alignas(64) long long value;
} PaddedCounter;

Counter shared_line[THREADS];
PaddedCounter separate_lines[THREADS];

int main(void)
{
    double start, end;

    // Experiment 1: Adjacent counters
    start = omp_get_wtime();

    #pragma omp parallel num_threads(THREADS)
    {
        int id = omp_get_thread_num();

        for (long long i = 0; i < ITERATIONS; i++)
            shared_line[id].value++;
    }

    end = omp_get_wtime();
    double false_sharing_time = end - start;

    // Experiment 2: Padded counters
    start = omp_get_wtime();

    #pragma omp parallel num_threads(THREADS)
    {
        int id = omp_get_thread_num();

        for (long long i = 0; i < ITERATIONS; i++)
            separate_lines[id].value++;
    }

    end = omp_get_wtime();
    double padded_time = end - start;

    printf("False sharing time: %.6f seconds\n",
           false_sharing_time);

    printf("Padded counter time: %.6f seconds\n",
           padded_time);

    if (padded_time > 0.0) {
        printf("Improvement ratio: %.2fx\n",
               false_sharing_time / padded_time);
    }

    printf("Expected counter: %lld\n",
           (long long)THREADS * ITERATIONS);

    for (int i = 0; i < THREADS; i++) {
        if (shared_line[i].value != ITERATIONS ||
            separate_lines[i].value != ITERATIONS) {
            fprintf(stderr, "Counter verification failed for thread %d\n", i);
            return 1;
        }
    }

    return 0;
}
