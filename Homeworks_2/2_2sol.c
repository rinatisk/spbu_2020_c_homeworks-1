#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int digits = 10;

int getUniqueNumber(bool* arrayOfDigits)
{
    int uniqueNumber = 0;
    srand(time(NULL));
    do {
        uniqueNumber = rand() % 10;
    } while (arrayOfDigits[uniqueNumber]);
    return uniqueNumber;
}

int* getComputerGuess(int computerGuess[], int tryLength)
{
    bool* arrayOfDigits = malloc(digits * sizeof(bool));
    memset(arrayOfDigits, false, digits);
    for (int i = 0; i < tryLength; ++i) {
        computerGuess[i] = getUniqueNumber(arrayOfDigits);
        arrayOfDigits[computerGuess[i]] = true;
    }
    free(arrayOfDigits);
    return computerGuess;
}

int* getUserTry(int userTry[], int tryLength)
{
    printf("Write you numbers\n");
    int n = 0;
    scanf("%d", &n);
    for (int i = 0; i < tryLength; ++i) {
        userTry[i] = n % 10;
        n = n / 10;
    }
    return userTry;
}

bool isUserWin(int numberOfBulls, int tryLength)
{
    return numberOfBulls == tryLength;
}

void printGuessInfo(int numberOfBulls, int numberOfCows, int tryLength)
{
    if (isUserWin(numberOfBulls, tryLength)) {
        printf("You win\n");
    }
    else
        printf("Cows: %d Bulls: %d\n", numberOfCows, numberOfBulls);
}

int countCows(int computerGuess[], int userTry[], int tryLength)
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

int countBulls(int computerGuess[], int userTry[], int tryLength)
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
    int tryLength = 0;
    printf("write number length:\n");
    scanf("%d", &tryLength);
    int* computerGuess = calloc(tryLength, sizeof(int));
    int* userTry = calloc(tryLength, sizeof(int));
    computerGuess = getComputerGuess(computerGuess, tryLength);
    int numberOfBulls = 0;
    int numberOfCows = 0;
    while (!isUserWin(numberOfBulls, tryLength)) {
        userTry = getUserTry(userTry, tryLength);
        numberOfBulls = countBulls(computerGuess, userTry, tryLength);
        numberOfCows = countCows(computerGuess, userTry, tryLength);
        printGuessInfo(numberOfBulls, numberOfCows, tryLength);
    }
    free(computerGuess);
    free(userTry);
    return 0;
}