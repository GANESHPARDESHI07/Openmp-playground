#include <stdio.h>
#include <omp.h>

int main()
{
    int total = 0;
    int count = 0;

    #pragma omp parallel num_threads(4)
    {
        int id = omp_get_thread_num();

        #pragma omp critical
        {
            printf("Thread %d is running\n", id);
        }

        for (int i = 0; i < 100000; i++)
        {
            #pragma omp critical
            {
                total += 2;
                count++;
            }
        }
    }

    printf("\nExpected total: 800000\n");
    printf("Actual total:   %d\n", total);

    printf("Expected count: 400000\n");
    printf("Actual count:   %d\n", count);

    return 0;
}