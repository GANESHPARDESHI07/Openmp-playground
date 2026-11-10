
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10000000
#define RUNS 5

double a[N], b[N], c_normal[N], c_simd[N];

void normal_add(void)
{
    for (int i = 0; i < N; i++)
        c_normal[i] = a[i] + b[i];
}

void simd_add(void)
{
    #pragma omp simd
    for (int i = 0; i < N; i++)
        c_simd[i] = a[i] + b[i];
}

double benchmark(void (*function)(void))
{
    double total = 0.0;

    for (int r = 0; r < RUNS; r++) {
        double start = omp_get_wtime();
        function();
        total += omp_get_wtime() - start;
    }

    return total / RUNS;
}

int main(void)
{
    for (int i = 0; i < N; i++) {
        a[i] = i * 1.5;
        b[i] = i * 2.5;
    }

    double normal_time = benchmark(normal_add);
    double simd_time = benchmark(simd_add);

    int correct = 1;

    for (int i = 0; i < N; i++) {
        if (c_normal[i] != c_simd[i]) {
            correct = 0;
            break;
        }
    }

    printf("Normal loop: %.6f seconds\n", normal_time);
    printf("SIMD loop:   %.6f seconds\n", simd_time);
    printf("Speedup:     %.2fx\n", normal_time / simd_time);
    printf("Results match: %s\n", correct ? "YES" : "NO");

    return correct ? 0 : 1;
}
