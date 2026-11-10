#include <stdio.h>
#include <math.h>
#include <omp.h>

#define N 500
#define RUNS 5

double A[N][N], B[N][N];
double C_seq[N][N], C_par[N][N];

void initialize_matrices()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i][j] = (i + j) % 10;
            B[i][j] = (i - j) % 10;
        }
    }
}

// Sequential cache-optimized multiplication
void matrix_sequential()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            C_seq[i][j] = 0;

    for (int i = 0; i < N; i++)
    {
        for (int k = 0; k < N; k++)
        {
            double temp = A[i][k];

            for (int j = 0; j < N; j++)
                C_seq[i][j] += temp * B[k][j];
        }
    }
}

// OpenMP parallel cache-optimized multiplication
void matrix_parallel()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            C_par[i][j] = 0;

    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; i++)
    {
        for (int k = 0; k < N; k++)
        {
            double temp = A[i][k];

            for (int j = 0; j < N; j++)
                C_par[i][j] += temp * B[k][j];
        }
    }
}

int main()
{
    initialize_matrices();

    // Warm-up
    matrix_sequential();
    matrix_parallel();

    double seq_time = 0;
    double par_time = 0;

    for (int run = 0; run < RUNS; run++)
    {
        double start = omp_get_wtime();
        matrix_sequential();
        seq_time += omp_get_wtime() - start;

        start = omp_get_wtime();
        matrix_parallel();
        par_time += omp_get_wtime() - start;
    }

    int correct = 1;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (fabs(C_seq[i][j] - C_par[i][j]) > 1e-9)
            {
                correct = 0;
                break;
            }
        }
    }

    double avg_seq = seq_time / RUNS;
    double avg_par = par_time / RUNS;

    double speedup = avg_seq / avg_par;
    double efficiency = speedup / omp_get_max_threads() * 100.0;

    printf("\nMatrix size: %d x %d\n", N, N);
    printf("Threads: %d\n", omp_get_max_threads());

    printf("\nSequential i-k-j: %.6f seconds\n", avg_seq);
    printf("Parallel i-k-j:   %.6f seconds\n", avg_par);

    printf("\nSpeedup: %.2fx\n", speedup);
    printf("Parallel efficiency: %.2f%%\n", efficiency);

    printf("Correctness: %s\n", correct ? "PASSED" : "FAILED");

    return 0;
}