#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    
    int n = 1000;
    int arr[n];

    
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100; 
    }

 
    int sum = 0;

    
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

   
    printf("The sum of the array elements is: %d\n", sum);

    return 0;
}
