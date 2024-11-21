#include <mpi.h>
#include <stdio.h>
#include <unistd.h> 

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char hostname[256];
    gethostname(hostname, sizeof(hostname));

    printf("Process %d running on host %s\n", rank, hostname);

    char message[100];

    if (rank == 0) {
    
        snprintf(message, sizeof(message), "Hello from process %d!", rank);

        for (int i = 1; i < size; i++) {
            MPI_Send(message, sizeof(message), MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    } else {

        MPI_Recv(message, sizeof(message), MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Process %d received message: %s\n", rank, message);
    }
    MPI_Finalize();

    return 0;
}
