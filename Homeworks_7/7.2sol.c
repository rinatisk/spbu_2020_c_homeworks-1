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

bool isCityInState(int* citiesInState, int citiesInStateNumber, int cityNumber)
{
    bool isFind = false;
    for (int i = 0; i < citiesInStateNumber; ++i) {
        isFind += citiesInState[i] == cityNumber;}
    return isFind;
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

int** addCapitalToStates(int quantityOfCities, int quantityOfState, int* citiesInState, FILE* file)
{
    if (quantityOfState == 0 || quantityOfCities == 0 || citiesInState == NULL) {
        return NULL;
    }
    int** states = allocStates(quantityOfCities, quantityOfState);
    for (int i = 0; i < quantityOfState; ++i) {
        citiesInState[i] = states[i][0];
        states[i][0] = getNumberFromFile(file) - 1;
        citiesInState[i] = states[i][0];
    }
    return states;
}

int addCityToState(Graph* graphOfCities, int citiesInState, int quantityOfCity, int* citiesInStateArray, int** states, int stateNumber)
{
    int toAddCity = 0;
    int toAddIndex = 0;
    int shortestRoad = 0;
    for (int i = 0; states[stateNumber][toAddIndex] != -1; ++i) {
        toAddIndex = i + 1;
    }
    bool isFirstLength = true;
    bool isCurrentIndexes = false;
    bool isNewMinimum = false;
    for (int i = 0; i < toAddIndex; ++i) {
        for (int j = 0; j < quantityOfCity; ++j) {
            int currentLength = getLengthFromEdge(graphOfCities, states[stateNumber][i], j);
            isCurrentIndexes = !isCityInState(citiesInStateArray, citiesInState, j);
            isNewMinimum = ((currentLength < shortestRoad) || isFirstLength);
            if (isCurrentIndexes && isNewMinimum) {
                shortestRoad = currentLength;
                toAddCity = j;
                isFirstLength = false;
            }
        }
    }
    states[stateNumber][toAddIndex] = toAddCity;
    citiesInStateArray[citiesInState] = toAddCity;
    return citiesInState + 1;
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
    int* citiesInStateArray = addCitiesInState(quantityOfCity);
    int quantityOfCitiesInState = quantityOfState;
    int** states = addCapitalToStates(quantityOfCity, quantityOfState, citiesInStateArray, text);
    Graph* graphOfCities = createGraph(quantityOfRoads, quantityOfCity + 1, roads);
    for (int loop = 0; loop < ((quantityOfCity - quantityOfState) / quantityOfState + 1); ++loop) {
        if (quantityOfCitiesInState == quantityOfCity) {
            break;
        }
        for (int i = 0; i < quantityOfState; ++i) {
            quantityOfCitiesInState = addCityToState(graphOfCities, quantityOfCitiesInState, quantityOfCity, citiesInStateArray, states, i);
            if (quantityOfCitiesInState == quantityOfCity) {
                break;
            }
        }
    }

    printCities(states, quantityOfState, quantityOfCity);

    fclose(text);
    free(citiesInStateArray);
    dynamic_array_free(states, quantityOfState);
    removeEdgeArray(roads, quantityOfRoads);
    removeGraph(graphOfCities);

    return 0;
}
