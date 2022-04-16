// -----------------  Unblocked ------------------------ //
#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]){
        // Given
        int rank, size;
        float start, end, value;
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        start = MPI_Wtime();

        MPI_Request ireq;
        MPI_Status  istatus;

        //unblocked using MPI_WAIT?
        if(rank == 0){
                value = 12.34;
                MPI_Isend(&value, 1,MPI_FLOAT, 1,0,MPI_COMM_WORLD, &ireq);
                MPI_Wait(&ireq, &istatus);
                printf("\nNon-Blocking Rank 0:\n");
                printf("Proces 0 has sent %f to process 1\n", value);
        }
        else if(rank == 1){
                MPI_Irecv(&value, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &ireq);
                MPI_Wait(&ireq, &istatus);
                printf("\nNon-Blocking Rank 1:\n");
                printf("Process 1 has recieved number %f from process 0\n", value);
                end = MPI_Wtime();
                printf("Execution time of: %f for process of rank %d\n", end-start, rank);
        }
        //end = MPI_Wtime();
        //printf("\tExecution time of: %f for process of rank %d\n", end-start, rank);
        // printf("Process %d has recieved the number = %f\n", rank, value);
        MPI_Finalize();
        return 0;
}
