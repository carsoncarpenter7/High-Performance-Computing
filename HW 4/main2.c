
#include <stdio.h>
#include <omp.h>
#define N 33 // N = 32 (size) + 1

// gcc-11  -fopenmp main3.c
// ./a.out
int main (int argc, char *argv[]) {

int th_id, nthreads;
int b[N];
int i;
omp_set_num_threads(8);

 /* Initialize arrays a */
    for (int i = 0; i < N; i++) {
        b[i] = i;
    }

#pragma omp parallel private(th_id)
    {
    th_id = omp_get_thread_num();
    // printf("Thread %d\n", th_id);

// #pragma omp barrier       // <----------- master waits until all threads finish before printing 
   /* Parallel Loop to set array values. */
#pragma omp for schedule(static,1) 
    for (int i = 0; i < N; i++) {
        b[i] = i;
        printf("Thread %d is initializing Array[%d] to %d\n", th_id, i, b[i]);
    }
    }
}