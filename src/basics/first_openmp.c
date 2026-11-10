#include <stdio.h>
#include <omp.h>

int main()
{
    #pragma omp parallel num_threads(4)
    {
        int id = omp_get_thread_num();

        printf("Thread %d is working\n", id);

        #pragma omp barrier

        if (id == 0)
        {
            printf("All threads have reached the barrier!\n");
        }
    }

    printf("Program finished\n");

    return 0;
}