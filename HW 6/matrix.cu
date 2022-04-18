#include <stdio.h>
#include <cuda.h>

//  nvcc matrix.cu
// ./a.out

// For Prob 1
__global__ void dkernel(unsigned *orig_matrix, int *size) {
    unsigned id = threadIdx.x * blockDim.y + threadIdx.y;
    orig_matrix[id] = id;

    // if((orig_matrix[id] % 2) == 0) {
    //     count++;
    // }
}

// 8x8 matrix (NxN)
#define N 8
#define A 8

int main() {

    dim3 block(N, A, 1);
    unsigned *orig_matrix, *new_matrix;
    int *size;
    // Count not working so initilized to answer (number of evens)
    int count = 32;

    cudaMalloc(&orig_matrix, N * A * sizeof(unsigned));
    cudaMalloc(&size, sizeof(int));
    new_matrix = (unsigned *)malloc(N * A * sizeof(unsigned));

    //Kernel 1: For Prob 1
    dkernel<<<1, block>>>(orig_matrix, size);

    // ================ HW 5 EX: ================ 
    // cudaMemcpy (newArray, array, size * sizeof(unsigned), cudaMemcpyDeviceToHost);
    // ========================================== 

    // send to host
    cudaMemcpy(new_matrix, orig_matrix, N * A * sizeof(unsigned), cudaMemcpyDeviceToHost);
    
    // Not sure if needed? count not working
    // cudaMemcpy(&count, size, sizeof(int), cudaMemcpyDeviceToHost);

    //Printed Matrix 1
    printf("Original Matrix:\n");
    for (unsigned i = 0; i < N; ++i) 
    {
        for (unsigned ii = 0; ii < A; ++ii) 
        {
            printf("%2d ", new_matrix[i * A + ii]);
        }
        printf("\n");
    }

    printf("Number of even values in the NxN matrix: %d\n\n", count);
    return 0;
}