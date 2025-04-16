#include "kruskal.h"
#include "disjoint_set.h"
#include <algorithm>
#include <iostream>
#include "graph_list.h"

Kruskal::Kruskal() {
}

std::vector<Edge> Kruskal::findMSTHelper(std::vector<Edge>& edges, int numVertices) {
    std::vector<Edge> mstEdges;
    std::sort(edges.begin(), edges.end());
    DisjointSet ds(numVertices);
    for (const auto& edge : edges) {
        int rootU = ds.findSet(edge.from);
        int rootV = ds.findSet(edge.to);
       if (rootU != rootV) {
            mstEdges.push_back(edge);
            ds.unionSets(rootU, rootV);
        } else {
            std::cout << "Cycle detected: Edge (" << edge.from << ", " << edge.to << ") skipped.\n";
        }
    }
    return mstEdges;
}

std::vector<Edge> Kruskal::findMST(GraphMatrix& graph) {
    std::vector<Edge> edges = graph.getEdges();
    int numVertices = graph.getNumVertices();
    return findMSTHelper(edges, numVertices);
}
    
std::vector<Edge> Kruskal::findMST(GraphList& graph) {
    std::vector<Edge> edges = getEdgesList(&graph);
    int numVertices = graph.numVertices;
    return findMSTHelper(edges, numVertices);
}