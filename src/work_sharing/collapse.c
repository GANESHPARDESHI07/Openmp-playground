
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define N 512
#define RUNS 5

static double A[N][N], B[N][N];
static double C_normal[N][N], C_collapse[N][N];

void initialize_matrices(void)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = (double)(i + j) / N;
            B[i][j] = (double)(i - j + N) / N;
        }
    }
}

void multiply_normal(void)
{
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double sum = 0.0;

            for (int k = 0; k < N; k++)
                sum += A[i][k] * B[k][j];

            C_normal[i][j] = sum;
        }
    }
}

void multiply_collapse(void)
{
    #pragma omp parallel for collapse(2) schedule(static)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double sum = 0.0;

            for (int k = 0; k < N; k++)
                sum += A[i][k] * B[k][j];

            C_collapse[i][j] = sum;
        }
    }
}

double benchmark(void (*function)(void))
{
    double total = 0.0;

    for (int run = 0; run < RUNS; run++) {
        double start = omp_get_wtime();
        function();
        total += omp_get_wtime() - start;
    }

    return total / RUNS;
}

int main(void)
{
    initialize_matrices();

    double normal_time = benchmark(multiply_normal);
    double collapse_time = benchmark(multiply_collapse);

    int correct = 1;

    for (int i = 0; i < N && correct; i++) {
        for (int j = 0; j < N; j++) {
            if (fabs(C_normal[i][j] - C_collapse[i][j]) > 1e-9) {
                correct = 0;
                break;
            }
        }
    }

    printf("Matrix size: %d x %d\n", N, N);
    printf("Threads available: %d\n", omp_get_max_threads());
    printf("Normal parallel time:   %.6f seconds\n", normal_time);
    printf("Collapse(2) time:       %.6f seconds\n", collapse_time);
    printf("Speedup (normal/collapse): %.2fx\n",
           normal_time / collapse_time);
    printf("Results match: %s\n", correct ? "YES" : "NO");

    return correct ? 0 : 1;
}
