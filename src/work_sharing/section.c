#include <stdio.h>
#include <omp.h>

int main()
{
    #pragma omp parallel num_threads(3)
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                printf("Matrix multiplication: Thread %d\n",
                       omp_get_thread_num());
            }

            #pragma omp section
            {
                printf("Data preprocessing: Thread %d\n",
                       omp_get_thread_num());
            }

            #pragma omp section
            {
                printf("Model evaluation: Thread %d\n",
                       omp_get_thread_num());
            }
        }
    }

    printf("All sections completed.\n");

    return 0;
}