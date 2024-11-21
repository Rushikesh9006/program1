#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
   
    int n = 1000;
    int arr[n];

   
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000; 
    }

    

    
    int max_val = arr[0];

   
    #pragma omp parallel
    {
        int local_max = arr[0];

        #pragma omp for
        for (int i = 0; i < n; i++) {
            if (arr[i] > local_max) {
                local_max = arr[i];
            }
        }

        /
        #pragma omp critical
        {
            if (local_max > max_val) {
                max_val = local_max;
            }
        }
    }

  
    printf("The maximum value in the array is: %d\n", max_val);

    return 0;
}
