#include <stdio.h>
#include <cuda.h>

// For Prob 1
__global__ void dkernel(unsigned *array, int size)
{
    unsigned id = blockIdx.x * blockDim.x + threadIdx.x;
    if (id < size)
    {
        // For Prob 1 
        array[id] = 0;
    }
}

// For Prob 3
__global__ void kernel(unsigned *array, int size)
{
    unsigned id = blockIdx.x * blockDim.x + threadIdx.x;
    if (id < size)
    {
        // For Prob 3
        array[id] = id;
    }
}

// Dont change??
#define BLOCKSIZE 1024

int main(void) {
    // For Prob 1 
    unsigned size = 32;

    // For Prob 2/3
    // unsigned size = 1024

    // For Prob 4
    // unsigned size = 8000;

    unsigned *array, *newArray;
    cudaMalloc(&array, size * sizeof(unsigned));

    newArray = (unsigned *)malloc(size * sizeof(unsigned));
    unsigned nblocks = ceil((float) size / BLOCKSIZE);

    printf ("This is an array of size %d and filled with 0's. \n", size);

    //Kernel 1: For Prob 1/2
    dkernel<<<nblocks, BLOCKSIZE>>> (array, size);

    // Kernel 2: For Prob 3/4
    // kernel<<<nblocks, BLOCKSIZE>>> (array, size);

    cudaMemcpy (newArray, array, size * sizeof(unsigned), cudaMemcpyDeviceToHost);
    
    // Print Array
    for (unsigned ai = 0; ai < size; ++ai) 
    {
        printf("%4d \n", newArray[ai]);
    }
}