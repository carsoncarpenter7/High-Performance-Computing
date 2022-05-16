## Exercise 1. 
Write either a single program or two separate C/C++ programs that use(s) MPI blocking and non-blocking commands MPI_Send, MPI_Rcvd, MPI_Isend and MPI_Ircvd to exchange one float value between process with rank 0 and process with rank 1. Calculate the execution time using MPI_Wtime to compute the execution time and write it down in the table below as follows:

                                                                     
__**A single transmission using blocking communication**__ 

__**A single transmission using non blocking communication**__  

__**Two transmissions (round trip) using blocking communication**__

__**Two transmissions (round trip) using non blocking communication**__



## Exercise 2.
Modify the ring example given in class to calculate the execution time using MPI_Wtime of the transmission of the value 7 from process with rank 0 to process with rank 1, etc. until the value is received back at the process with rank 0. Use only blocking communication. Launch the execution of the program with a varied number of parallel processes (mpirun -n 10 ./a.out to launch the executable a.out for 10 processes) and write down the execution time of the ring example as follows:

__**Ring with 4 nodes**__

__**Ring with 8 nodes**__

__**Ring with 10 nodes**__

__**Ring with 12 nodes**__

