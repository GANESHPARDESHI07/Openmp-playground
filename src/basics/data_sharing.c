#include <stdio.h>
#include <omp.h>

int main()
{
    int shared_value = 100;
    int private_value = -1;

    #pragma omp parallel num_threads(4) \
        shared(shared_value) private(private_value)
    {
        int id = omp_get_thread_num();

        private_value = id * 10;

        printf("Thread %d: shared = %d, private = %d\n",
               id, shared_value, private_value);
    }

    printf("\nOutside parallel region:\n");
    printf("shared_value = %d\n", shared_value);
    printf("private_value = %d\n", private_value);

    return 0;
}