#include <stdio.h>
#include <omp.h>

int main(){
    #pragma omp parallel for schedule(guided)
    for(int i = 0; i < 30; i++){
        int thread_id = omp_get_thread_num();
        printf("Thread %d is processing iteration %d\n", thread_id, i);
    }
    return 0;
}