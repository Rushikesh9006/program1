#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    
    char message[50];

    if (rank == 0) {
    
        strcpy(message, "Awaiting 2025");

    
        for (int i = 1; i < size; i++) {
            MPI_Send(message, strlen(message) + 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
        printf("Process %d sent the message: %s\n", rank, message);
    } else {
    
        MPI_Recv(message, sizeof(message), MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Process %d received the message: %s\n", rank, message);
    }

    MPI_Finalize();

    return 0;
}
