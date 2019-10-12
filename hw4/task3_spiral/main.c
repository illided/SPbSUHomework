#include <stdio.h>
#include <stdlib.h>
#include "simpleArrays.h"

void printRing(int **matrix, int center, int radius)
{
    for (int i = 0; i < 2 * radius; i++)
    {
        printf("%d ", matrix[center - i + radius - 1][center - radius]);
    }

    printArrayOfInt(center - radius + 1, center + radius, 1, matrix[center - radius]);

    for (int i = 0; i < 2 * radius; i++)
    {
        printf("%d ", matrix[center + i - radius + 1][center + radius]);
    }

    printArrayOfInt(center + radius - 1, center - radius, - 1, matrix[center + radius]);
}

int main() {
    /* This solution is splitting the matrix into the "rings"
     * (like this:
     *
     * 3 3 3 3 3
     * 3 2 2 2 3
     * 3 2 1 2 3
     * 3 2 2 2 3
     * 3 3 3 3 3 )
     *
     * and printing it ring by ring (clockwise) */

    printf("Enter the n:\n");  // creating the matrix and scanning it
    int matrixDimension = 0;
    scanf("%d", &matrixDimension);
    if ((matrixDimension % 2 == 0) || (matrixDimension < 1))
    {
        printf("Incorrect input");
        return 0;
    }

    printf("Enter the matrix:\n");
    int **matrix = malloc(sizeof(int*) * matrixDimension);
    for (int i = 0; i < matrixDimension; i++)
    {
        matrix[i] = createArrayOfInt(matrixDimension);
        scanArrayOfInt(0, matrixDimension - 1, matrix[i]);
    }

    printf("Answer: \n");
    printf("%d ", matrix[matrixDimension / 2][matrixDimension / 2]);  // print central element
    for (int radius = 1; radius <= matrixDimension / 2; radius++)  // print all the rings
    {
        printRing(matrix, matrixDimension / 2, radius);
    }

    for (int i = 0; i < matrixDimension; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}