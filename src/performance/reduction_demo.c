
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10000000

int main()
{
    long long *arr = malloc(N * sizeof(long long));

    if (arr == NULL)
    {
        perror("Memory allocation failed");
        return 1;
    }

    // Initialize array
    for (int i = 0; i < N; i++)
    {
        arr[i] = 1;
    }

    long long sequential_sum = 0;
    long long parallel_sum = 0;

    double start, end;
    double sequential_time, parallel_time;

    // -------------------------------
    // 1. Sequential execution
    // -------------------------------

    start = omp_get_wtime();

    for (int i = 0; i < N; i++)
    {
        sequential_sum += arr[i];
    }

    end = omp_get_wtime();

    sequential_time = end - start;

    // -------------------------------
    // 2. Parallel execution
    // -------------------------------

    start = omp_get_wtime();

    #pragma omp parallel for reduction(+:parallel_sum) num_threads(4)
    for (int i = 0; i < N; i++)
    {
        parallel_sum += arr[i];
    }

    end = omp_get_wtime();

    parallel_time = end - start;
    double speedup = parallel_time > 0.0
                         ? sequential_time / parallel_time
                         : 0.0;

    // -------------------------------
    // 3. Display results
    // -------------------------------

    printf("\n========== BENCHMARK RESULTS ==========\n");

    printf("Array size       : %d\n", N);

    printf("\nSequential sum   : %lld\n", sequential_sum);
    printf("Sequential time  : %.6f seconds\n", sequential_time);

    printf("\nParallel sum     : %lld\n", parallel_sum);
    printf("Parallel time    : %.6f seconds\n", parallel_time);

    if (parallel_time > 0)
    {
        printf("\nSpeedup          : %.2fx\n",
               sequential_time / parallel_time);
    }

    printf("=======================================\n");

    FILE *fp = fopen("results/sequential_results.txt", "a");

    if (fp == NULL)
    {
        perror("File opening failed");
        free(arr);
        return 1;
    }

    fprintf(fp, "Array size: %d\n", N);
    fprintf(fp, "Sequential sum: %lld\n", sequential_sum);
    fprintf(fp, "Sequential time: %.6f seconds\n", sequential_time);
    fprintf(fp, "Parallel sum: %lld\n", parallel_sum);
    fprintf(fp, "Parallel time: %.6f seconds\n", parallel_time);
    fprintf(fp, "Speedup: %.2fx\n\n", speedup);

    fclose(fp);
    free(arr);
    printf("\nResults saved to results/sequential_results.txt\n");
    return 0;
}
