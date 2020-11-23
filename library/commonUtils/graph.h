#ifndef SPBU_2020_C_HOMEWORKS_1_GRAPH_H
#define SPBU_2020_C_HOMEWORKS_1_GRAPH_H

#include <stdbool.h>


typedef struct Graph Graph;
typedef struct Edge Edge;

Graph* createGraph(int countEdges, int countVertex, Edge** edges);
bool depthFirstSearch(Graph* graph, int currentVertex, int* vertexState);
bool isConnected(int fromVertex, int toVertex, Graph* graph);
Edge* createEdge(int start, int end, int weight, bool oriented);
bool isCycled(Graph* graph);
Edge** createEdgeArray(int sizeOfArray);
int getOriginalAuthor(Graph* graphOfStudents, int studentNumber);
bool removeGraph(Graph* toRemoveGraph);
bool removeEdgeArray(Edge** toRemoveEdgeArray, int sizeOfArray);
bool removeEdge(Edge* toRemoveEdge);

#endif //SPBU_2020_C_HOMEWORKS_1_GRAPH_H
