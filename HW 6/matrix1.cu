#include <stdio.h>
#include <cuda.h>

//  nvcc matrix.cu
// ./a.out

// From Prob 1 (keep to intitilize matrix)
__global__ void dkernel(unsigned *orig_matrix, int *size) {
    // initialize matrix
    unsigned id = threadIdx.x * blockDim.y + threadIdx.y;
    orig_matrix[id] = id;

    // if((orig_matrix[id] % 2) == 0) {
    //     count++;
    // }
}

// For Prob 2
__global__ void kernal ( unsigned *orig_matrix, unsigned *result, unsigned size) {
    // Compute square kernal
    unsigned id = blockIdx.x * blockDim.x + threadIdx.x;
    for (unsigned i = 0; i < size; ++i) 
    {
        for (unsigned ii = 0; ii < size; ++ii) 
        {
            // multiply/combine original matrixes
            result[id * size + i] += orig_matrix[id * size + ii] *
            orig_matrix[ii * size + i];
        }
    }
}

// 8x8 matrix (NxN)
#define N 8
#define M 8

int main() {

    dim3 block(N, M, 1);
    unsigned *orig_matrix, *new_matrix, *result, *squared;
    int *size;

    cudaMalloc(&orig_matrix, N * M * sizeof(unsigned));
    cudaMalloc(&size, sizeof(int));
    new_matrix = (unsigned *)malloc(N * M * sizeof(unsigned));

    //Kernel 1: For Prob 1
    dkernel<<<1, block>>>(orig_matrix, size);

    // ================ HW 5 EX: ================ 
    // cudaMemcpy (newArray, array, size * sizeof(unsigned), cudaMemcpyDeviceToHost);
    // ========================================== 

     // send to host
    cudaMemcpy(new_matrix, orig_matrix, N * M * sizeof(unsigned), cudaMemcpyDeviceToHost);
    
    // Not sure if needed? count not working
    //cudaMemcpy(&count, size, sizeof(int), cudaMemcpyDeviceToHost);
    
    // For Prob 2
    squared = (unsigned *)malloc(N * M * sizeof(unsigned));
    cudaMalloc(&result, N * M * sizeof(unsigned));

    //Kernel 2: For Prob 2
    kernal<<<1, N>>>(orig_matrix, result, N);

    // send to host
    cudaMemcpy(squared, result, N * M * sizeof(unsigned), cudaMemcpyDeviceToHost);

    //Printed Matrix 1
    printf("Compute Square:\n");
    for (unsigned i = 0; i < N; ++i) 
    {
        for (unsigned ii = 0; ii < N; ++ii) 
        { 
            printf("%2d ", squared[i * N + ii]); 
        } 
        printf("\n"); 
    } 

    return 0;
}