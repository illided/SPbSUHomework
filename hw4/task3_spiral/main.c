#include <stdio.h>
#include <stdlib.h>
#include "simpleArrays.h"

int main() {
    printf("Enter the n:\n");  // creating the matrix and scanning it
    int matrixDimension = 0;
    scanf("%d", &matrixDimension);
    printf("Enter the matrix:\n");
    int **matrix = malloc(sizeof(int*) * matrixDimension);
    for (int i = 0; i < matrixDimension; i++)
    {
        matrix[i] = createArrayOfInt(matrixDimension);
        scanArrayOfInt(0, matrixDimension - 1, matrix[i]);
    }

    return 0;
}