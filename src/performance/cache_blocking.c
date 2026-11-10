
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 512
#define BLOCK_SIZE 32
#define RUNS 5

static double A[N][N];
static double B[N][N];
static double C_unblocked[N][N];
static double C_blocked[N][N];

void initialize_matrices(void)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = (double)((i + j) % 10);
            B[i][j] = (double)((i - j + 10) % 10);
        }
    }
}

void multiply_unblocked(void)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            C_unblocked[i][j] = 0.0;

    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            double temp = A[i][k];

            for (int j = 0; j < N; j++) {
                C_unblocked[i][j] += temp * B[k][j];
            }
        }
    }
}

void multiply_blocked(void)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            C_blocked[i][j] = 0.0;

    for (int ii = 0; ii < N; ii += BLOCK_SIZE) {
        for (int kk = 0; kk < N; kk += BLOCK_SIZE) {
            for (int jj = 0; jj < N; jj += BLOCK_SIZE) {

                for (int i = ii; i < ii + BLOCK_SIZE; i++) {
                    for (int k = kk; k < kk + BLOCK_SIZE; k++) {
                        double temp = A[i][k];

                        for (int j = jj; j < jj + BLOCK_SIZE; j++) {
                            C_blocked[i][j] += temp * B[k][j];
                        }
                    }
                }
            }
        }
    }
}

int verify_results(void)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (fabs(C_unblocked[i][j] - C_blocked[i][j]) > 1e-9)
                return 0;
        }
    }

    return 1;
}

int main(void)
{
    initialize_matrices();

    double unblocked_total = 0.0;
    double blocked_total = 0.0;

    // Warm-up
    multiply_unblocked();
    multiply_blocked();

    for (int run = 0; run < RUNS; run++) {
        double start = omp_get_wtime();
        multiply_unblocked();
        unblocked_total += omp_get_wtime() - start;

        start = omp_get_wtime();
        multiply_blocked();
        blocked_total += omp_get_wtime() - start;
    }

    double unblocked_avg = unblocked_total / RUNS;
    double blocked_avg = blocked_total / RUNS;

    printf("\nMatrix size: %d x %d\n", N, N);
    printf("Block size: %d x %d\n", BLOCK_SIZE, BLOCK_SIZE);

    printf("\nUnblocked average: %.6f seconds\n", unblocked_avg);
    printf("Blocked average:   %.6f seconds\n", blocked_avg);

    printf("Speedup: %.2fx\n", unblocked_avg / blocked_avg);

    printf("Correctness: %s\n",
           verify_results() ? "PASSED" : "FAILED");

    return 0;
}
