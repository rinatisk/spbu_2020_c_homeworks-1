#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const int tryLength = 4;

int* getComputerGuess(int computerGuess[])
{
    for (int i = 0; i < tryLength; ++i) {
        computerGuess[i] = rand() % 6;
    }
    return computerGuess;
}

int* getUserTry(int userTry[])
{
    printf("Write you numbers throw a space\n");
    for (int i = 0; i < tryLength; ++i) {
        scanf("%d", &userTry[i]);
    }
    return userTry;
}

bool isUserWin(int numberOfBulls)
{
    return numberOfBulls == tryLength;
}

void printGuessInfo(int numberOfBulls, int numberOfCows)
{
    if (isUserWin(numberOfBulls)) {
        printf("You win\n");
    } else
        printf("Cows: %d Bulls: %d\n", numberOfCows, numberOfBulls);
}

int countCows(int computerGuess[], int userTry[])
{
    int numberOfCows = 0;
    for (int i = 0; i < tryLength; ++i) {
        for (int j = 0; j < tryLength; ++j) {
            if ((userTry[i] == computerGuess[j]) && (i != j)) {
                numberOfCows++;
                break;
            }
        }
    }
    return numberOfCows;
}

int countBulls(int computerGuess[], int userTry[])
{
    int numberOfBulls = 0;
    for (int i = 0; i < tryLength; ++i) {
        if (computerGuess[i] == userTry[i]) {
            numberOfBulls++;
            userTry[i] = -1; // remove bulls because they break counting cows
        }
    }
    return numberOfBulls;
}

int main()
{
    int* computerGuess = calloc(tryLength, tryLength * sizeof(int));
    int* userTry = calloc(tryLength, tryLength * sizeof(int));
    computerGuess = getComputerGuess(computerGuess);
    int numberOfBulls = 0;
    int numberOfCows = 0;
    while (!isUserWin(numberOfBulls)) {
        userTry = getUserTry(userTry);
        numberOfBulls = countBulls(computerGuess, userTry);
        numberOfCows = countCows(computerGuess, userTry);
        printGuessInfo(numberOfBulls, numberOfCows);
    }
    free(computerGuess);
    free(userTry);
}