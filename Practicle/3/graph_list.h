#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

#include <cstddef>
#include <vector>
#include "graph_matrix.h"

// Structure for an arc node (representing an edge)
typedef struct ArcNode {
    int dest; // Destination vertex of the edge
    int weight; // Weight of the edge
    struct ArcNode* nextarc; // Pointer to the next arc
} ArcNode;

// Structure for a graph node (representing a vertex)
typedef struct GraphNode {
    int info; // Data associated with the vertex (optional)
    struct GraphNode* nextnode; // Pointer to the next vertex
    ArcNode* arcptr; // Pointer to the list of arcs (edges)
} GraphNode;

// Structure for the graph
typedef struct GraphList {
    GraphNode* head; // Pointer to the first vertex in the graph
    int numVertices;
} GraphList;

// Function prototypes
ArcNode* createArcNode(int dest);
GraphNode* createGraphNode(int info);
GraphList* createGraph();
void addVertex(GraphList* graph, int info);
GraphNode* findVertex(GraphList* graph, int info);
void addEdge(GraphList* graph, int src, int dest, int weight);
void displayAdjacencyList(GraphList* graph);
std::vector<Edge> getEdgesList(GraphList* graph);

#endif