#include <stdio.h>
#include "graph.h"
#include <stdlib.h>

int getVariant(Graph* studentGraph, int student)
{
    for (int i = 1; i < 4; i++)
    {
        if (areConnected(studentGraph, i, student))
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    FILE* students = fopen("students.txt", "r");
    if (students == NULL)
    {
        fprintf(stderr, "Can't open the file");
        return 1;
    }

    int studentArrayLength = 0;
    int studentArraySize = 0;
    fscanf(students, "%d", &studentArraySize);
    int* studentArray = malloc(sizeof(int) * studentArraySize);

    Graph* studentGraph = createGraph();
    int firstStudent = 0;
    int secondStudent = 0;

    while (!feof(students))
    {
        fscanf(students, "%d", &firstStudent);
        fscanf(students, "%d", &secondStudent);

        if (studentArrayLength == studentArraySize)
        {
            fprintf(stderr, "Too many students, expected: %d\n", studentArraySize);
            deleteGraph(studentGraph);
            free(studentArray);
            return 1;
        }
        studentArray[studentArrayLength] = firstStudent;
        studentArrayLength++;

        addToGraph(studentGraph, firstStudent);
        addToGraph(studentGraph, secondStudent);
        setConnection(studentGraph, firstStudent, secondStudent);
    }
    fclose(students);

    printf("Answer:\n");
    for (int i = 0; i < studentArrayLength; i++)
    {
        printf("%d %d\n", studentArray[i], getVariant(studentGraph, studentArray[i]));
    }
    free(studentArray);
    deleteGraph(studentGraph);
    return 0;
}
