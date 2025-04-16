#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#include <iostream>
#include <vector>
#include <tuple>
#include <cstddef>

struct Edge {
    int from;
    int to;
    int weight;
    Edge(int u, int v, int w) : from(u), to(v), weight(w) {}
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class GraphMatrix {
public:
    GraphMatrix(int n);
    void addEdge(int u, int v, int w);
    void printAdjacencyMatrix();
    std::vector<Edge> getEdges() const; //Add const here
    int getNumVertices() const { return numVertices; }
    std::vector<std::vector<int>> getAdjacencyMatrix() const;
private:
    int numVertices;
    std::vector<std::vector<int>> adjacencyMatrix;
};

#endif