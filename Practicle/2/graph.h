#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <limits>

class Graph {
public:
    int numVertices;
    std::vector<std::vector<int> > adjMatrix;

    Graph(int vertices);
    void addEdge(int u, int v, int weight);
    void printGraph();
};

#endif
