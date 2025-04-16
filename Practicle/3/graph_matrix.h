#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#include <iostream>
#include <vector>
#include <tuple>
#include <cstddef>

// Forward declaration of Edge struct
struct Edge; 

class GraphMatrix {
public:
    GraphMatrix(int n);
    void addEdge(int u, int v, int w);
    void printAdjacencyMatrix();
    std::vector<Edge> getEdges() const;
    int getNumVertices() const { return numVertices; }
private:
    int numVertices;
    std::vector<std::vector<int>> adjacencyMatrix;
};

// Definition of Edge struct outside the class
struct Edge {
    int from;
    int to;
    int weight;
    Edge(int u, int v, int w) : from(u), to(v), weight(w) {}
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

#endif