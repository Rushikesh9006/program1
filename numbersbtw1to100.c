#include <mpi.h>
#include <stdio.h>
#include <math.h>


int is_prime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

int main(int argc, char** argv) {
    
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    
    int start = 1;
    int end = 100000000;

   
    int range = (end - start + 1) / size;
    int local_start = start + rank * range;
    int local_end = (rank == size - 1) ? end : (local_start + range - 1);

   
    int local_prime_count = 0;
    for (int i = local_start; i <= local_end; i++) {
        if (is_prime(i)) {
            local_prime_count++;
        }
    }

   
    int total_prime_count = 0;
    MPI_Reduce(&local_prime_count, &total_prime_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

   
    if (rank == 0) {
        printf("Total number of primes between %d and %d is: %d\n", start, end, total_prime_count);
    }

   
    MPI_Finalize();

    return 0;
}
