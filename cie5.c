#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int send_array[4];      // Array at process 0
    int recv_value;         // Each process receives one element
    int gather_array[4];    // Gathered squared results at process 0

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 4) {
        if (rank == 0) {
            printf("Please run this program with 4 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        // Initialize the array at process 0
        send_array[0] = 1;
        send_array[1] = 2;
        send_array[2] = 3;
        send_array[3] = 4;
    }

    // Scatter 1 element from process 0 to each process
    MPI_Scatter(send_array, 1, MPI_INT, &recv_value, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process squares its received value
    int squared = recv_value * recv_value;
    printf("Process %d got %d → squared = %d\n", rank, recv_value, squared);

    // Gather squared values back to process 0
    MPI_Gather(&squared, 1, MPI_INT, gather_array, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Process 0 prints the gathered results
    if (rank == 0) {
        printf("Gathered result at Process 0: [");
        for (int i = 0; i < size; i++) {
            printf("%d", gather_array[i]);
            if (i != size - 1) printf(", ");
        }
        printf("]\n");
    }

    MPI_Finalize();
    return 0;
}
