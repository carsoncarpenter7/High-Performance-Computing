Compile: mpicc main.cpp
Execute Code: mpirun --oversubscribe -n 8 ./a.out
OR with enough pre-allocated slots: mpirun -n 8 ./a.out

__** --oversubscribe is used to allocate more "slots" on the computer to allow more processes **__
