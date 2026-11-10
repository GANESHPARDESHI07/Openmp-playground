
#include <stdio.h>
#include <omp.h>

int main(void)
{
    omp_set_max_active_levels(2);

    #pragma omp parallel num_threads(2)
    {
        int outer_id = omp_get_thread_num();

        printf("Outer: Thread %d | Team size: %d\n",
               outer_id, omp_get_num_threads());

        #pragma omp parallel num_threads(2)
        {
            printf("  Inner: Outer thread %d | Inner thread %d"
                   " | Team size: %d | Level: %d\n",
                   outer_id,
                   omp_get_thread_num(),
                   omp_get_num_threads(),
                   omp_get_level());
        }
    }

    return 0;
}
