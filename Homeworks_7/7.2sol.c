#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../library/commonUtils/arrayOperations.h"
#include "../library/commonUtils/graph.h"

const int NoRoad = -1;

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

    int index = -1;

    while (isdigit(number[index]) || index == -1) {
        ++index;
        number = realloc(number, (index + 1) * sizeof(char));
        number[index] = fgetc(file);
    }
    number[index] = '\n';
    int newNumber = getNewNumber(number);
    free(number);
    return newNumber;
}

int* addCitiesInState(int quantityOfCity)
{
    if (quantityOfCity <= 0) {
        return NULL;
    }
    int* usedCities = (int*)malloc(quantityOfCity * sizeof(int));
    memset(usedCities, NoRoad, quantityOfCity * sizeof(int));
    return usedCities;
}

Edge** getRoadsFromFile(int quantityOfRoads, FILE* file)
{
    Edge** roads = (Edge**)malloc(quantityOfRoads * sizeof(Edge*));
    for (int i = 0; i < quantityOfRoads; ++i) {
        int fromCity = getNumberFromFile(file);
        int toCity = getNumberFromFile(file);
        int length = getNumberFromFile(file);
        roads[i] = createEdge(fromCity - 1, toCity - 1, length, false);
    }
    return roads;
}

bool isCityInState(int* usedCities, int usedCitiesNumber, int city)
{
    for (int i = 0; i < usedCitiesNumber; ++i) {
        if (usedCities[i] == city) {
            return true;
        }
    }
    return false;
}

int** allocStates(int quantityOfCities, int quantityOfState)
{
    if (quantityOfState == 0 || quantityOfCities == 0) {
        return NULL;
    }
    int** states = malloc(quantityOfState * sizeof(int*));
    for (int i = 0; i < quantityOfState; ++i) {
        states[i] = (int*)malloc(quantityOfCities * sizeof(int));
        memset(states[i], NoRoad, quantityOfCities * sizeof(int));
    }
    return states;
}

int** addCapitalToStates(int quantityOfCities, int quantityOfState, int* usedCities, FILE* file)
{
    if (quantityOfState == 0 || quantityOfCities == 0 || usedCities == NULL) {
        return NULL;
    }
    int** states = allocStates(quantityOfCities, quantityOfState);
    for (int i = 0; i < quantityOfState; ++i) {
        usedCities[i] = states[i][0];
        states[i][0] = getNumberFromFile(file) - 1;
        usedCities[i] = states[i][0];
    }
    return states;
}

int addCityToState(int* usedCities, int usedCitiesNumber, int stateIndex, Graph* graphOfCities, int** states, int quantityOfCity)
{
    int shortestRoad = 0;
    int toAddCity = 0;
    int noRoadIndex = 0;
    bool isFirstLength = true;
    bool isCurrentIndexes = false;
    bool isNewMinimum = false;
    for (int i = 0; noRoadIndex == 0; ++i) {
        if (states[stateIndex][i] == NoRoad) {
            noRoadIndex = i;
            break;
        }
        for (int j = 0; j < quantityOfCity; ++j) {
            int currentLength = getLengthFromEdge(graphOfCities, states[stateIndex][i], j);
            isCurrentIndexes = !isCityInState(usedCities, usedCitiesNumber, j);
            isNewMinimum = ((currentLength < shortestRoad) || isFirstLength);
            if (isCurrentIndexes && isNewMinimum) {
                shortestRoad = currentLength;
                toAddCity = j;
                isFirstLength = false;
            }
        }
    }
    states[stateIndex][noRoadIndex] = toAddCity;
    usedCities[usedCitiesNumber] = toAddCity;
    return usedCitiesNumber + 1;
}

void printCities(int** states, int quantityOfState, int quantityOfCities)
{
    for (int i = 0; i < quantityOfState; ++i) {
        printf("State - %d\nCities: (", i + 1);
        for (int j = 0; j < quantityOfCities; ++j) {
            if (states[i][j] == NoRoad) {
                printf(" )");
                break;
            }
            printf(" %d", states[i][j] + 1);
        }
        printf("\n\n");
    }
}

int main()
{
    FILE* text = fopen("../Homeworks_7/text.txt", "r");

    int quantityOfCity = getNumberFromFile(text);
    int quantityOfRoads = getNumberFromFile(text);
    Edge** roads = getRoadsFromFile(quantityOfRoads, text);
    int quantityOfState = getNumberFromFile(text);
    int* usedCities = addCitiesInState(quantityOfCity);
    int quantityOfCitiesInState = quantityOfState;
    int** states = addCapitalToStates(quantityOfCity, quantityOfState, usedCities, text);
    Graph* graphOfCities = createGraph(quantityOfRoads, quantityOfCity + 1, roads);
    for (int loop = 0; loop < ((quantityOfCity - quantityOfState) / quantityOfState + 1); ++loop) {
        if (quantityOfCitiesInState == quantityOfCity) {
            break;
        }
        for (int i = 0; i < quantityOfState; ++i) {
            quantityOfCitiesInState = addCityToState(usedCities, quantityOfCitiesInState, i, graphOfCities, states, quantityOfCity);
            if (quantityOfCitiesInState == quantityOfCity) {
                break;
            }
        }
    }

    printCities(states, quantityOfState, quantityOfCity);

    fclose(text);
    free(usedCities);
    dynamic_array_free(states, quantityOfState);
    removeEdgeArray(roads, quantityOfRoads);
    removeGraph(graphOfCities);

    return 0;
}
