//  In addition to what Problem 1 and Problem 2 ask, 
//  create another parallel construct that calculates 
//  the number of even values in array as follows: 
//  it distributes the iterations to each thread using cyclic distribution, 
//  each thread computes the number of even values 
//  from its iterations and master thread collects and 
//  adds the number of even values. Master thread then 
//  displays the result.

#include <stdio.h>
#include <omp.h>
#include <stdbool.h>
#define N 33 // N = 32 (size) + 1

// gcc-11  -fopenmp main3.c
// ./a.out
int main (int argc, char *argv[]) {

int th_id, nthreads;
int a[N], b[N];
int i;
omp_set_num_threads(8);

 /* Initialize arrays a */
    for (int i = 0; i < N; i++) {
        a[i] = i;
    }

#pragma omp parallel private(th_id)
    {
    th_id = omp_get_thread_num();
    // printf("Thread %d\n", th_id);

   /* Parallel Loop to set array values. */
#pragma omp for schedule(static,1) 
    for (int i = 1; i < N; i++) {
        a[i] = 0;
        printf("Thread %d is initializing Array[%d] to %d\n", th_id, i, a[i]);
    }
    }

#pragma omp parallel private(th_id)
    {
    th_id = omp_get_thread_num();
    // printf("Thread %d\n", th_id);
    
/* Parallel Loop to set array values. */
#pragma omp for schedule(static,1) 
    for (int i = 1; i < N; i++) {
        a[i] = i;
        printf("Thread %d is initializing Array[%d] to %d\n", th_id, i, a[i]);
    }

    int count = 0;
    int even;
#pragma omp parallel
#pragma omp single
{
    th_id = omp_get_thread_num();
    for (int i = 1; i < N; i++) {
        if (a[i] % 2){
            count++;
        }
        a[i] = count;
        even = a[i];
        //printf("Total Even Values in Array: %d\n", a[(sizeof(i)/sizeof(int))-1]);
        if (even > 15) {
            printf("Total Even Values in Array: %d\n", even);
        }
    }
    //printf("Total Even Values in Array: %d\n", even);
    }
}
}
