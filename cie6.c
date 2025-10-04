#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size;
    int reduce_sum, allreduce_sum;

    MPI_Init(&argc, &argv);                 // Initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // Get current process rank
    MPI_Comm_size(MPI_COMM_WORLD, &size);   // Get total number of processes

    // Each process has its rank as a value
    int value = rank;

    // MPI_Reduce: sum of ranks at process 0
    MPI_Reduce(&value, &reduce_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("MPI_Reduce result at Process 0: Sum of ranks = %d\n", reduce_sum);
    }

    // MPI_Allreduce: sum of ranks shared with all processes
    MPI_Allreduce(&value, &allreduce_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    printf("MPI_Allreduce result at Process %d: Sum of ranks = %d\n", rank, allreduce_sum);

    MPI_Finalize(); // Finalize MPI
    return 0;
}
