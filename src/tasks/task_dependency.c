#include <stdio.h>
#include <omp.h>

int main()
{
    int data = 0;
    int processed = 0;

    #pragma omp parallel num_threads(3)
    {
        #pragma omp single
        {
            #pragma omp task depend(out: data)
            {
                data = 100;
                printf("Task A: Data loaded by thread %d\n",
                       omp_get_thread_num());
            }

            #pragma omp task depend(in: data) depend(out: processed)
            {
                processed = data * 2;
                printf("Task B: Data processed by thread %d\n",
                       omp_get_thread_num());
            }

            #pragma omp task depend(in: processed)
            {
                printf("Task C: Final result = %d, thread %d\n",
                       processed, omp_get_thread_num());
            }

            #pragma omp taskwait
        }
    }

    return 0;
}