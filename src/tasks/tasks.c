#include <stdio.h>
#include <omp.h>

int main()
{
    #pragma omp parallel num_threads(3)
    {
        #pragma omp single
        {
            #pragma omp task
            {
                printf("Task 1: Preprocessing | Thread %d\n",
                       omp_get_thread_num());
            }

            #pragma omp task
            {
                printf("Task 2: Feature extraction | Thread %d\n",
                       omp_get_thread_num());
            }

            #pragma omp task
            {
                printf("Task 3: Model evaluation | Thread %d\n",
                       omp_get_thread_num());
            }

            #pragma omp taskwait
            printf("All tasks completed.\n");
        }
    }

    return 0;
}