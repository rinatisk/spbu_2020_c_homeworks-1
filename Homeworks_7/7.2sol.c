#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../library/commonUtils/arrayOperations.h"
#include "../library/commonUtils/graph.h"

const int NoRoad = -1;

typedef struct States {
    int** statesMatrix;
    int* citiesInStateArray;
    int quantityOfState;
    int quantityOfCities;
} States;

States* createState(int* citiesInStateArray, int** statesMatrix, int quantityOfState, int quantityOfCities)
{
    States* states = malloc(sizeof(States));
    states->statesMatrix = statesMatrix;
    states->citiesInStateArray = citiesInStateArray;
    states->quantityOfState = quantityOfState;
    states->quantityOfCities = quantityOfCities;
    return states;
}

bool deleteStates(States* states)
{
    dynamic_array_free(states->statesMatrix, states->quantityOfState);
    dynamic_array_free_one_dim(states->citiesInStateArray);
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
    int* citiesInState = (int*)malloc(quantityOfCity * sizeof(int));
    memset(citiesInState, NoRoad, quantityOfCity * sizeof(int));
    return citiesInState;
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

bool isCityInState(int* citiesInState, int cityNumber)
{
    return citiesInState[cityNumber] == cityNumber;
}

int** allocStates(int quantityOfCities, int quantityOfState)
{
    if (quantityOfState == 0 || quantityOfCities == 0) {
        return NULL;
    }
    int** statesMatrix = malloc(quantityOfState * sizeof(int*));
    for (int i = 0; i < quantityOfState; ++i) {
        statesMatrix[i] = (int*)malloc(quantityOfCities * sizeof(int));
        memset(statesMatrix[i], NoRoad, quantityOfCities * sizeof(int));
    }
    return statesMatrix;
}

int** addCapitalToStates(int quantityOfCities, int quantityOfState, int* citiesInState, FILE* file)
{
    if (quantityOfState == 0 || quantityOfCities == 0 || citiesInState == NULL) {
        return NULL;
    }
    int** statesMatrix = allocStates(quantityOfCities, quantityOfState);
    for (int i = 0; i < quantityOfState; ++i) {
        citiesInState[i] = statesMatrix[i][0];
        statesMatrix[i][0] = getNumberFromFile(file) - 1;
        citiesInState[statesMatrix[i][0]] = statesMatrix[i][0];
    }
    return statesMatrix;
}

int findToAddIndex(States* states, int stateNumber)
{
    int toAddIndex = 0;
    for (int i = 0; states->statesMatrix[stateNumber][toAddIndex] != -1; ++i) {
        toAddIndex = i + 1;
    }
    return toAddIndex;
}

int addCityToState(Graph* graphOfCities, int citiesInState, int quantityOfCity, States* states, int stateNumber)
{
    int toAddCity = 0;
    int toAddIndex = findToAddIndex(states, stateNumber);
    int shortestRoad = 0;
    bool isFirstLength = true;
    bool isCurrentIndexes = false;
    bool isNewMinimum = false;
    for (int i = 0; i < toAddIndex; ++i) {
        for (int j = 0; j < quantityOfCity; ++j) {
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
    states->statesMatrix[stateNumber][toAddIndex] = toAddCity;
    states->citiesInStateArray[toAddCity] = toAddCity;
    return citiesInState + 1;
}

void addingCitiesToStates(int quantityOfCitiesInState, Graph* graphOfCities, States* states)
{
    for (int loop = 0; loop < ((states->quantityOfCities - states->quantityOfState) / states->quantityOfState + 1); ++loop) {
        if (quantityOfCitiesInState == states->quantityOfCities) {
            break;
        }
        for (int i = 0; i < states->quantityOfState; ++i) {
            quantityOfCitiesInState = addCityToState(graphOfCities, quantityOfCitiesInState, states->quantityOfCities, states, i);
            if (quantityOfCitiesInState == states->quantityOfCities) {
                break;
            }
        }
    }
}

void printCities(States* states)
{
    for (int i = 0; i < states->quantityOfState; ++i) {
        printf("State with capital - %d\nCities: (", states->statesMatrix[i][0] + 1);
        for (int j = 0; states->statesMatrix[i][j] != NoRoad; ++j) {
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
    int* citiesInStateArray = addCitiesInState(quantityOfCity);
    int quantityOfCitiesInState = quantityOfState;
    int** statesMatrix = addCapitalToStates(quantityOfCity, quantityOfState, citiesInStateArray, text);
    States* states = createState(citiesInStateArray, statesMatrix, quantityOfState, quantityOfCity);
    Graph* graphOfCities = createGraph(quantityOfRoads, quantityOfCity + 1, roads);
    addingCitiesToStates(quantityOfCitiesInState, graphOfCities, states);

    printCities(states);

    fclose(text);
    deleteStates(states);
    removeEdgeArray(roads, quantityOfRoads);
    removeGraph(graphOfCities);

    return 0;
}
