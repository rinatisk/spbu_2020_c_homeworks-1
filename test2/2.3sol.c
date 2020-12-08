#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../library/commonUtils/arrayOperations.h"

void countedUnattainableVertex(bool* alreadyArray, int edges, int vertex, int** matrix, int fromVertex)
{
    for (int i = 0; i < edges; ++i) {
        if (matrix[fromVertex - 1][i] == 1) {
            for (int j = fromVertex - 1; j < vertex; ++j) {
                if (matrix[j][i] == -1 && !alreadyArray[j]) {
                    alreadyArray[j] = true;
                    countedUnattainableVertex(alreadyArray, edges, vertex, matrix, j + 1);
                }
            }
        }
    }
}

void printInfoAboutVertexes(bool* alreadyCounted, int vertex, int fromVertex)
{
    for (int i = 0; i < vertex; ++i) {
        if (!alreadyCounted[i] && i != fromVertex - 1) {
            printf("%d ", i + 1);
        }
    }
}

int main()
{
    int edges = 0;
    int vertex = 0;
    printf("write throw the space number of edges and vertex\n");
    scanf("%d %d", &edges, &vertex);
    int** matrix = dynamic_array_alloc(vertex, edges);
    printf("write matrix, for example if edges = 6 and vertex = 5 you can write matrix:\n"
           "-1 1 -1 0 -1 0\n"
           "1 0 0 -1 0 0\n"
           "0 -1 0 0 0 1\n"
           "0 0 1 0 0 -1\n"
           "0 0 0 1 1 0\n");
    for (int i = 0; i < vertex; ++i) {
        for (int j = 0; j < edges; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("write number from vertex:\n");
    bool* alreadyCountedArray = calloc(vertex, sizeof(bool));
    memset(alreadyCountedArray, false, vertex * sizeof(bool));
    int fromVertex = 0;
    scanf("%d", &fromVertex);

    countedUnattainableVertex(alreadyCountedArray, edges, vertex, matrix, fromVertex);
    printInfoAboutVertexes(alreadyCountedArray, vertex, fromVertex);

    dynamic_array_free(matrix, vertex);
    free(alreadyCountedArray);
}