#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int array[5]; // Array of 5 integers

    MPI_Init(&argc, &argv);                 // Initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // Get current process ID
    MPI_Comm_size(MPI_COMM_WORLD, &size);   // Get total number of processes

    if (rank == 0) {
        // Process 0 reads array from user
        printf("Enter 5 integers: ");
        for (int i = 0; i < 5; i++) {
            scanf("%d", &array[i]);
        }
    }

    // Broadcast the array from process 0 to all processes
    MPI_Bcast(array, 5, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process prints the array it received
    printf("Process %d received array: ", rank);
    for (int i = 0; i < 5; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    MPI_Finalize(); // Finalize MPI
    return 0;
}
