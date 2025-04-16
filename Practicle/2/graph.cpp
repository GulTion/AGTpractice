#include "graph.h"
#include <iostream>

Graph::Graph(int vertices) {
    numVertices = vertices;
    adjMatrix.resize(vertices, std::vector<int>(vertices, 0));
}

void Graph::addEdge(int u, int v, int weight) {
    adjMatrix[u][v] = weight;
    adjMatrix[v][u] = weight;
}

void Graph::printGraph() {
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            std::cout << adjMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
