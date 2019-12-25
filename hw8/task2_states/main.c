#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* citiesFile = fopen("cities.txt", "r");
    if (citiesFile == NULL)
    {
        fprintf(stderr, "Cant open the file");
        return 1;
    }

    Graph* countryGraph = createGraph();
    int numOfRoads = 0;
    int numOfCities = 0;
    int firstCity = 0;
    int secondCity = 0;
    int roadLength = 0;
    fscanf(citiesFile, "%d %d", &numOfCities, &numOfRoads);
    for (int i = 0; i < numOfRoads; i++)
    {
        fscanf(citiesFile, "%d %d %d", &firstCity, &secondCity, &roadLength);
        addToGraph(countryGraph, firstCity);
        addToGraph(countryGraph, secondCity);
        setConnection(countryGraph, firstCity, secondCity, roadLength);
    }

    int numOfCapitals = 0;
    fscanf(citiesFile, "%d", &numOfCapitals);
    if (numOfCapitals > numOfCities)
    {
        fprintf(stderr, "Too many capitals, expected less than %d\n", numOfCities);
        deleteGraph(countryGraph);
        return 1;
    }

    int* capitalsArray = malloc(sizeof(int) * numOfCapitals);
    for (int i = 0; i < numOfCapitals; i++)
    {
        fscanf(citiesFile, "%d", &capitalsArray[i]);
    }

    Graph* solutionGraph = getClustering(countryGraph, capitalsArray, numOfCapitals);
    if (solutionGraph != NULL)
    {
        printClustering(solutionGraph, capitalsArray, numOfCapitals);
        deleteGraph(solutionGraph);
    }
    else
    {
        printf("Something went wrong. Please check if the input correct\n");
    }
    deleteGraph(countryGraph);
    free(capitalsArray);
    return 0;
}
