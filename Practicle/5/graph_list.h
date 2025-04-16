#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

#include <cstddef>
#include <vector>
#include "graph_matrix.h"

typedef struct ArcNode {
    int dest;
    int weight; 
    struct ArcNode* nextarc;
} ArcNode;

typedef struct GraphNode {
    int info;
    struct GraphNode* nextnode;
    ArcNode* arcptr;
} GraphNode;

typedef struct GraphList {
    GraphNode* head; 
    int numVertices;
    int getNumVertices();
} GraphList;

ArcNode* createArcNode(int dest);
GraphNode* createGraphNode(int info);
GraphList* createGraph();
void addVertex(GraphList* graph, int info);
GraphNode* findVertex(GraphList* graph, int info);
void addEdge(GraphList* graph, int src, int dest, int weight);
void displayAdjacencyList(GraphList* graph);
std::vector<Edge> getEdgesList(GraphList* graph);

#endif
