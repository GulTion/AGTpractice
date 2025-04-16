#include "prim.h"
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

void Prim::primsMST(Graph& g) {
    int numVertices = g.numVertices;

    // Priority queue to store vertices with min key value
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >, std::greater<std::pair<int, int> > > pq;

    int startVertex = 0;

    std::vector<int> key(numVertices, std::numeric_limits<int>::max());
    std::vector<int> parent(numVertices, -1);
    std::vector<bool> inMST(numVertices, false);

    pq.push(std::make_pair(0, startVertex));
    key[startVertex] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (int v = 0; v < numVertices; ++v) {
            int weight = g.adjMatrix[u][v];

            if (weight != 0 && !inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push(std::make_pair(key[v], v));
            }
        }
    }

    std::cout << "Edge \tWeight\n";
    for (int i = 1; i < numVertices; ++i) {
        std::cout << parent[i] << " - " << i << "\t" << g.adjMatrix[i][parent[i]] << "\n";
    }
}
