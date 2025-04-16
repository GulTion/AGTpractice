#include "vertex_cover.h"
#include <algorithm>

std::vector<int> approxVertexCoverMatrix(const GraphMatrix& graph) {
    std::vector<int> cover;
    std::vector<std::vector<int>> adjMatrix = graph.getAdjacencyMatrix();
    int numVertices = graph.getNumVertices();

    std::vector<bool> visited(numVertices, false);

    for (int u = 0; u < numVertices; ++u) {
        if (!visited[u]) {
            for (int v = 0; v < numVertices; ++v) {
                if (adjMatrix[u][v] == 1 && !visited[v]) {
                    cover.push_back(u);
                    cover.push_back(v);
                    visited[u] = true;
                    visited[v] = true;
                    break; 
                }
            }
        }
    }

    return cover;
}

std::vector<int> approxVertexCoverList(GraphList& graph) {
    std::vector<int> cover;
    int numVertices = graph.numVertices;
    std::vector<bool> visited(numVertices, false);

    GraphNode* temp = graph.head;
    while (temp != NULL) {
        int u = temp->info;
        if (!visited[u]) {
            ArcNode* arcTemp = temp->arcptr;
            while (arcTemp != NULL) {
                int v = arcTemp->dest;
                if (!visited[v]) {
                    cover.push_back(u);
                    cover.push_back(v);
                    visited[u] = true;
                    visited[v] = true;
                    break; 
                }
                arcTemp = arcTemp->nextarc;
            }
        }
        temp = temp->nextnode;
    }

    return cover;
}