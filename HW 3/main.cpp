#include <iostream>
#include <cstdlib>
#include <ctime>

#include <stdio.h>
#include "mpi.h"
using namespace std;

// mpicc main.cpp
// mpirun --oversubscribe -n 8 ./a.out

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    //printf("I am %d of %d\n", rank, size);

    srand(time(NULL) + rank);
    int input = (rand() % 20 + 1);
    int index = 1;
    int buffer = 0;
    //printf("Process %d has input = %d\n", rank, input);
    MPI_Scan(&input, &buffer, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    printf("Process %d will receive the array portion between index %d - %d\n", rank, (buffer - input) + 1, buffer);
    // printf("Process %d has number = %d\n", rank, index);
    MPI_Finalize();
    return 0;
}