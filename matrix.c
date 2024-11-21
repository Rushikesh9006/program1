#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ROWS 3
#define COLS 3

int main() {
    int A[ROWS][COLS], B[ROWS][COLS], C[ROWS][COLS];

    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            A[i][j] = rand() % 10; 
            B[i][j] = rand() % 10;
        }
    }

  
    printf("Matrix A:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");

    printf("Matrix B:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }

   
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

   
    printf("Matrix C (Result of A + B):\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
