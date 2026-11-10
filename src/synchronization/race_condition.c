#include <stdio.h>
#include <omp.h>

int main()
{
    int counter = 0;

    #pragma omp parallel num_threads(4)
    {

        #pragma omp single
        {
            printf("Threads running: %d\n", omp_get_num_threads());
        }

        for (int i = 0; i < 100000; i++)
        {
            counter++;
        }
    }

    printf("Expected counter: 400000\n");
    printf("Actual counter:   %d\n", counter);

    return 0;
}