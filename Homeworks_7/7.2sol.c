#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../library/commonUtils/arrayOperations.h"
#include "../library/commonUtils/graph.h"

typedef struct States {
    int** statesMatrix;
    bool* citiesInStateArray;
    int quantityOfState;
    int quantityOfCities;
    int* sizeOfState;
} States;

States* createState(bool* citiesInStateArray, int** statesMatrix, int quantityOfState, int quantityOfCities)
{
    States* states = malloc(sizeof(States));
    states->statesMatrix = statesMatrix;
    states->citiesInStateArray = citiesInStateArray;
    states->quantityOfState = quantityOfState;
    states->quantityOfCities = quantityOfCities;
    states->sizeOfState = calloc(states->quantityOfState, sizeof(int));
    for (int i = 0; i < quantityOfState; ++i) {
        states->sizeOfState[i] = 1;
    }
    return states;
}

bool deleteStates(States* states)
{
    dynamic_array_free(states->statesMatrix, states->quantityOfState);
    dynamic_array_free_one_dim(states->sizeOfState);
    free(states->citiesInStateArray);
    free(states);
    return true;
}

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
    int size = 1;

    while (isdigit(number[index]) || index == -1) {
        ++index;
        if (size == index - 1) {
            number = realloc(number, (size * 2) * sizeof(char));
            size *= 2;
        }
        number[index] = fgetc(file);
    }
    number[index] = '\n';
    int newNumber = getNewNumber(number);
    free(number);
    return newNumber;
}

bool* allocCitiesInState(int quantityOfCity)
{
    if (quantityOfCity <= 0) {
        return NULL;
    }
    bool* citiesInState = (bool*)malloc(quantityOfCity * sizeof(bool));
    memset(citiesInState, false, quantityOfCity * sizeof(bool));
    return citiesInState;
}

Edge** getRoadsFromFile(int quantityOfRoads, FILE* file)
{
    Edge** roads = createEdgeArray(quantityOfRoads);
    for (int i = 0; i < quantityOfRoads; ++i) {
        int fromCity = getNumberFromFile(file);
        int toCity = getNumberFromFile(file);
        int length = getNumberFromFile(file);
        roads[i] = createEdge(fromCity - 1, toCity - 1, length, false);
    }
    return roads;
}

bool isCityInState(bool* citiesInState, int cityNumber)
{
    return citiesInState[cityNumber];
}

int** allocStates(int quantityOfCities, int quantityOfState)
{
    if (quantityOfState == 0 || quantityOfCities == 0) {
        return NULL;
    }
    int** statesMatrix = malloc(quantityOfState * sizeof(int*));
    for (int i = 0; i < quantityOfState; ++i) {
        statesMatrix[i] = (int*)calloc(quantityOfCities, sizeof(int));
    }
    return statesMatrix;
}

int** addCapitalToStates(int quantityOfCities, int quantityOfState, bool* citiesInState, FILE* file)
{
    if (quantityOfState == 0 || quantityOfCities == 0 || citiesInState == NULL) {
        return NULL;
    }
    int** statesMatrix = allocStates(quantityOfCities, quantityOfState);
    for (int i = 0; i < quantityOfState; ++i) {
        statesMatrix[i][0] = getNumberFromFile(file) - 1;
        citiesInState[statesMatrix[i][0]] = true;
    }
    return statesMatrix;
}

int findToAddIndex(States* states, int stateNumber)
{
    int toAddIndex = states->sizeOfState[stateNumber];
    return toAddIndex;
}

int findToAddCity(Graph* graphOfCities, States* states, int stateNumber, int toAddIndex)
{
    int toAddCity = 0;
    int shortestRoad = 0;
    bool isFirstLength = true;
    bool isCurrentIndexes = false;
    bool isNewMinimum = false;
    for (int i = 0; i < toAddIndex; ++i) {
        for (int j = 0; j < states->quantityOfCities; ++j) {
            int currentLength = getLengthFromEdge(graphOfCities, states->statesMatrix[stateNumber][i], j);
            isCurrentIndexes = !isCityInState(states->citiesInStateArray, j);
            isNewMinimum = ((currentLength < shortestRoad) || isFirstLength);
            if (isCurrentIndexes && isNewMinimum) {
                shortestRoad = currentLength;
                toAddCity = j;
                isFirstLength = false;
            }
        }
    }
    return toAddCity;
}

bool addNewCityToState(Graph* graphOfCities, States* states, int stateNumber)
{
    if (graphOfCities == NULL || states == NULL) {
        return false;
    }
    int toAddIndex = findToAddIndex(states, stateNumber);
    int toAddCity = findToAddCity(graphOfCities, states, stateNumber, toAddIndex);
    states->statesMatrix[stateNumber][toAddIndex] = toAddCity;
    ++states->sizeOfState[stateNumber];
    states->citiesInStateArray[toAddCity] = true;
    return true;
}

bool isAllCitiesInStates(States* states)
{
    bool isAllCitiesInStates = true;
    for (int i = 0; i < states->quantityOfCities; ++i) {
        isAllCitiesInStates *= states->citiesInStateArray[i];
    }
    return isAllCitiesInStates;
}

void distributeCitiesToStates(Graph* graphOfCities, States* states)
{
    for (int loop = 0; loop < ((states->quantityOfCities - states->quantityOfState) / states->quantityOfState + 1); ++loop) {
        for (int i = 0; i < states->quantityOfState; ++i) {
            if (isAllCitiesInStates(states)) {
                return;
            }
            addNewCityToState(graphOfCities, states, i);
        }
    }
}

void printCities(States* states)
{
    for (int i = 0; i < states->quantityOfState; ++i) {
        printf("State with capital - %d\nCities: (", states->statesMatrix[i][0] + 1);
        for (int j = 0; j < states->sizeOfState[i]; ++j) {
            printf(" %d", states->statesMatrix[i][j] + 1);
        }
        printf(" )\n\n");
    }
}

int main()
{
    FILE* text = fopen("../Homeworks_7/text.txt", "r");
    if (text == NULL) {
        printf("couldn't open the file");
        return -1;
    }

    int quantityOfCity = getNumberFromFile(text);
    int quantityOfRoads = getNumberFromFile(text);
    Edge** roads = getRoadsFromFile(quantityOfRoads, text);
    int quantityOfState = getNumberFromFile(text);
    bool* citiesInStateArray = allocCitiesInState(quantityOfCity);
    int** statesMatrix = addCapitalToStates(quantityOfCity, quantityOfState, citiesInStateArray, text);
    States* states = createState(citiesInStateArray, statesMatrix, quantityOfState, quantityOfCity);
    Graph* graphOfCities = createGraph(quantityOfRoads, states->quantityOfCities + 1, roads);
    distributeCitiesToStates(graphOfCities, states);

    printCities(states);

    fclose(text);
    deleteStates(states);
    removeEdgeArray(roads, quantityOfRoads);
    removeGraph(graphOfCities);

    return 0;
}
