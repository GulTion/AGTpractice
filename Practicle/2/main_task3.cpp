#include "graph.h"
#include "prim.h"
#include <iostream>

int main() {

    int numVertices;

    std::cout << "Enter the number of vertices: ";
    std::cin >> numVertices;

    Graph g(numVertices);

    std::cout << "Enter the edges and weights (u v weight), enter -1 -1 -1 to stop:\n";
    int u, v, weight;
    while (true) {
        std::cin >> u >> v >> weight;
        if (u == -1 && v == -1 && weight == -1) {
            break;
        }
        g.addEdge(u, v, weight);
    }

    Prim prim;
    prim.primsMST(g);

    return 0;
}
