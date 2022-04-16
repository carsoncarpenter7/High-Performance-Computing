#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
        int rank, size;
        float start, end, value;
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        start = MPI_Wtime();

        MPI_Request ireq;
        MPI_Status  istatus;

        //blocking
        if (rank == 0) {
                value = 12.12;
                MPI_Send(&value, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD);
                printf("\nBlocking Rank 0: \n");
                printf("Process %d has sent %f to procces  1\n", rank, value);

                MPI_Recv(&value, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD, &istatus);
                printf("\nRecieving New Value: \n");
                printf("Process %d has recieved %f from process 1\n", rank ,value);

                end = MPI_Wtime();
                printf("\nCalculating Execution Time of Rank 0: \n");
                printf("\tExecution time of: %f for process of rank %d\n", end-start, rank);

        }
        else if (rank == 1) {
                MPI_Recv(&value, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &istatus);
                printf("\nBlocking Rank 1:\n");
                printf("Process 1 has recieved number %f from process 0\n", value);

                value = 17.12;
                MPI_Send(&value, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
                printf("Process %d has sent %f to process 0\n", rank, value);

                end = MPI_Wtime();
                // printf("\nTwo Trip Blocking Time Elapsed:\n");
                printf("\tExecution time of: %f for process of rank %d\n", end - start, rank);

        }
        end = MPI_Wtime();
        // printf("\nTest:\n");
        // printf("\tExecution time of: %f for process of rank %d\n", end-start, rank);
        MPI_Finalize();
        return 0;
}