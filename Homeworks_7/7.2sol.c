#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../library/commonUtils/arrayOperations.h"
#include "../library/commonUtils/graph.h"

int getNewNumber(char* string)
{
    int value = 0;
    int position = 0;
    while (isdigit(string[(position)])) {
        value *= 10;
        value += (string[position] - '0');
        (position) += 1;
    }
    return value;
}

int getNumberFromFile(FILE* file)
{
    char* number = (char*)malloc(sizeof(char));
    int index = 0;

    number[index] = fgetc(file);
    while (isdigit(number[index])) {
        ++index;
        number = realloc(number, (index + 1) * sizeof(char));
        number[index] = fgetc(file);
    }
    number[index] = '\0';
    int newNumber = getNewNumber(number);
    free(number);
    return newNumber;
}

void getRoadsFromFile(FILE* file, int quantityOfEdges, Edge** edges)
{
    for (int i = 0; i < quantityOfEdges; ++i) {
        int fromVertex = getNumberFromFile(file);
        int toVertex = getNumberFromFile(file);
        int length = getNumberFromFile(file);
        edges[i] = createEdge(fromVertex - 1, toVertex - 1, length, false);
    }
}

bool addStates(FILE* file, int quantityOfState, int** states, int* usedCities, int quantityOfCities)
{
    if (quantityOfState == 0 || quantityOfCities == 0 || states == NULL || usedCities == NULL) {
        return false;
    }
    for (int i = 0; i < quantityOfState; ++i) {
        states[i] = (int*)malloc(quantityOfCities * sizeof(int));
        memset(states[i], -1, quantityOfCities * sizeof(int));
        states[i][0] = getNumberFromFile(file) - 1;
        usedCities[i] = states[i][0];
    }
    return true;
}

bool isUsed(int* usedCities, int usedCitiesNumber, int city)
{
    for (int i = 0; i < usedCitiesNumber; ++i) {
        if (usedCities[i] == city) {
            return true;
        }
    }
    return false;
}

bool addCityToState(int** states, Graph* graphOfCities, int stateIndex, int quantityOfCity, int* usedCities, int usedCitiesNumber)
{
    int minLength = 0;
    int toAddCity = -1;
    int maxNotEmptyState = 0;
    bool isFirstLength = true;
    bool isCurrentIndexes = false;
    bool isNewMinimum = false;
    for (int i = 0; i < quantityOfCity; ++i) {
        if (states[stateIndex][i] == -1) {
            maxNotEmptyState = i;
            break;
        }
        for (int j = 0; j < quantityOfCity; ++j) {
            int currentLength = getLengthFromEdge(graphOfCities, states[stateIndex][i], j);
            isCurrentIndexes = j != i && !isUsed(usedCities, usedCitiesNumber, j);
            isNewMinimum = currentLength != 0 && ((currentLength < minLength) || isFirstLength);
            if (isCurrentIndexes && isNewMinimum) {
                isFirstLength = false;
                minLength = currentLength;
                toAddCity = j;
            }
        }
    }
    // if nowhere to add city
    if (toAddCity == -1) {
        return false;
    }
    states[stateIndex][maxNotEmptyState] = toAddCity;
    usedCities[usedCitiesNumber] = toAddCity;
    return true;
}

void printStates(int** states, int quantityOfState, int quantityOfCities)
{
    for (int i = 0; i < quantityOfState; ++i) {
        printf("State - %d\nCities: ", i + 1);
        for (int j = 0; j < quantityOfCities; ++j) {
            if (states[i][j] == -1) {
                break;
            }
            printf("%d ", states[i][j] + 1);
        }
        printf("\n\n");
    }
}

int main()
{
    FILE* text = fopen("../Homeworks_7/text.txt", "r");

    int quantityOfCity = getNumberFromFile(text);
    int quantityOfRoads = getNumberFromFile(text);

    Edge** roads = (Edge**)malloc(quantityOfRoads * sizeof(Edge*));
    getRoadsFromFile(text, quantityOfRoads, roads);

    int quantityOfState = getNumberFromFile(text);
    int** states = (int**)malloc(quantityOfState * sizeof(int*));

    int* usedCities = (int*)malloc(quantityOfCity * sizeof(int));
    memset(usedCities, -1, quantityOfCity * sizeof(int));
    addStates(text, quantityOfState, states, usedCities, quantityOfCity);

    Graph* graph = createGraph(quantityOfRoads, quantityOfCity, roads);
    int QuantityOfUsedCities = quantityOfState;
    while (QuantityOfUsedCities != quantityOfCity) {
        for (int i = 0; i < quantityOfState; ++i) {
            if (addCityToState(states, graph, i, quantityOfCity, usedCities, QuantityOfUsedCities)) {
                ++QuantityOfUsedCities;
            }
        }
    }

    printStates(states, quantityOfState, quantityOfCity);

    fclose(text);
    free(usedCities);
    dynamic_array_free(states, quantityOfState);
    removeEdgeArray(roads, quantityOfRoads);
    removeGraph(graph);

    return 0;
}
