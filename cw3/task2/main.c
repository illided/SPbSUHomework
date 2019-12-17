#include <stdio.h>
#include <stdlib.h>
#include <values.h>

double** readMatrix(int numOfRows, int numOfColumns)
{
    double** matrix = malloc(sizeof(double*) * numOfRows);
    for (int i = 0; i < numOfRows; i++)
    {
        matrix[i] = malloc(sizeof(double) * numOfColumns);
        printf("Enter row #%d:\n", i);
        for (int j = 0; j < numOfColumns; j++)
        {
            scanf("%lf", &matrix[i][j]);
        }
    }
    return matrix;
}

int main()
{
    int numOfRows = 0;
    int numOfColumns = 0;
    printf("Enter number of rows then number of columns:\n");
    scanf("%d %d", &numOfRows, &numOfColumns);
    double** matrix = readMatrix(numOfRows, numOfColumns);
    double currentColumnMaximum = MINDOUBLE;
    printf("Answer:\n");
    for (int i = 0; i < numOfColumns; i++)
    {
        for (int j = 0; j < numOfRows; j++)
        {
            if (currentColumnMaximum < matrix[j][i])
            {
                currentColumnMaximum = matrix[j][i];
            }
        }
        for (int j = 0; j < numOfRows; j++)
        {
            if (currentColumnMaximum == matrix[j][i])
            {
                double currentRowMinimum = MAXDOUBLE;
                for (int k = 0; k < numOfColumns; k++)
                {
                    if (currentRowMinimum > matrix[j][k])
                    {
                        currentRowMinimum = matrix[j][k];
                    }
                }
                if (currentColumnMaximum == currentRowMinimum)
                {
                    printf("Row: %d Column: %d Value: %lf\n", j, i, currentColumnMaximum);
                }
            }
        }
    }
    for (int i = 0; i < numOfRows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}
