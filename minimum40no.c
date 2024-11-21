#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char** argv) {
    
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

   
    const int total_numbers = 40;
    const int numbers_per_process = total_numbers / size;

   
    int numbers[total_numbers];
    if (rank == 0) {
        /
        for (int i = 0; i < total_numbers; i++) {
            numbers[i] = rand() % 100; 
        }

       
        printf("Input array:\n");
        for (int i = 0; i < total_numbers; i++) {
            printf("%d ", numbers[i]);
        }
        printf("\n");
    }

    
    int sub_numbers[numbers_per_process];

    
    MPI_Scatter(numbers, numbers_per_process, MPI_INT, sub_numbers,
                numbers_per_process, MPI_INT, 0, MPI_COMM_WORLD);

    
    int local_min = INT_MAX;
    for (int i = 0; i < numbers_per_process; i++) {
        if (sub_numbers[i] < local_min) {
            local_min = sub_numbers[i];
        }
    }

   
    int global_min;
    MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("The global minimum is: %d\n", global_min);
    }

   
    MPI_Finalize();

    return 0;
}
