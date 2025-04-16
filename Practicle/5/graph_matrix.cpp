#include "graph_matrix.h"
#include <iomanip>
#include <queue>
#include <cstddef>

GraphMatrix::GraphMatrix(int n) : numVertices(n), adjacencyMatrix(n, std::vector<int>(n, 0)) {
}

void GraphMatrix::addEdge(int u, int v, int w) {
    if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
        adjacencyMatrix[u][v] = w;
       adjacencyMatrix[v][u] = w;
   } else {
          std::cout << "Invalid edge indices." << std::endl;
  }
}

void GraphMatrix::printAdjacencyMatrix() {
    std::cout << "Adjacency Matrix:\n";
    std::cout << "    ";
    for (int i = 0; i < numVertices; ++i) {
       std::cout << std::setw(3) << i;
    }
    std::cout << "\n";
    for (int i = 0; i < numVertices; ++i) {
        std::cout << std::setw(3) << i << ": ";
        for (int j = 0; j < numVertices; ++j) {
            std::cout << std::setw(3) << adjacencyMatrix[i][j];
       }
        std::cout << "\n";
   }
}
    
std::vector<Edge> GraphMatrix::getEdges() const {
     std::vector<Edge> edges;
    for (int i = 0; i < numVertices; ++i) {
        for (int j = i + 1; j < numVertices; ++j) {
            if (adjacencyMatrix[i][j] != 0) {
                 edges.push_back(Edge(i, j, adjacencyMatrix[i][j]));
            }
       }
    }
   return edges;
}

std::vector<std::vector<int>> GraphMatrix::getAdjacencyMatrix() const {
    return adjacencyMatrix;
}