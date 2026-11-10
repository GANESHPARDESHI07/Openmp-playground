
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000

double A[N][N];
double B[N][N];
double C_seq[N][N];
double C_par[N][N];

int main()
{
    double start, end;
    double sequential_time, parallel_time;

    // --------------------------------
    // 1. Initialize matrices
    // --------------------------------

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }

    // --------------------------------
    // 2. Sequential multiplication
    // --------------------------------

    start = omp_get_wtime();

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            C_seq[i][j] = 0;

            for (int k = 0; k < N; k++)
            {
                C_seq[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    end = omp_get_wtime();
    sequential_time = end - start;

    // --------------------------------
    // 3. Parallel multiplication
    // --------------------------------

    start = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            C_par[i][j] = 0;

            for (int k = 0; k < N; k++)
            {
                C_par[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    end = omp_get_wtime();
    parallel_time = end - start;

    // --------------------------------
    // 4. Verify results
    // --------------------------------

    int correct = 1;

    for (int i = 0; i < N && correct; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (C_seq[i][j] != C_par[i][j])
            {
                correct = 0;
                break;
            }
        }
    }

    // --------------------------------
    // 5. Calculate performance
    // --------------------------------

    double speedup = sequential_time / parallel_time;

    printf("\n========== MATRIX BENCHMARK ==========\n");

    printf("Matrix Size       : %d x %d\n", N, N);

    printf("\nSequential Results\n");
    printf("Execution Time    : %.6f seconds\n", sequential_time);
    printf("C[0][0]           : %.2f\n", C_seq[0][0]);

    printf("\nParallel Results\n");
    printf("Execution Time    : %.6f seconds\n", parallel_time);
    printf("C[0][0]           : %.2f\n", C_par[0][0]);

    printf("\nPerformance\n");
    printf("Speedup           : %.2fx\n", speedup);
    printf("Result Verification: %s\n",
           correct ? "PASSED" : "FAILED");

    printf("======================================\n");

    // --------------------------------
    // 6. Save results
    // --------------------------------

    FILE *fp = fopen("results/sequential_results.txt", "a");

    if (fp == NULL)
    {
        perror("Unable to open results file");
        return 1;
    }

    fprintf(fp, "Matrix Size: %d x %d\n", N, N);
    fprintf(fp, "Sequential Time: %.6f seconds\n", sequential_time);
    fprintf(fp, "Parallel Time: %.6f seconds\n", parallel_time);
    fprintf(fp, "Speedup: %.2fx\n", speedup);
    fprintf(fp, "Verification: %s\n",
            correct ? "PASSED" : "FAILED");
    fprintf(fp, "--------------------------------------\n");

    fclose(fp);

    printf("\nResults saved to results/sequential_results.txt\n");

    return 0;
}
