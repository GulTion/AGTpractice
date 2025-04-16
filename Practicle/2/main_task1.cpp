#include "graph.h"
#include "prim.h"
#include <iostream>

int main() {


    int numVertices{9};



    Graph g(numVertices);

    g.addEdge(0, 1, 4);  // a-b
    g.addEdge(0, 7, 8);  // a-h
    g.addEdge(1, 2, 8);  // b-c
    g.addEdge(1, 7, 11); // b-h
    g.addEdge(2, 3, 7);  // c-d
    g.addEdge(2, 5, 4);  // c-f
    g.addEdge(2, 8, 2);  // c-i
    g.addEdge(3, 4, 9);  // d-e
    g.addEdge(3, 5, 14); // d-f
    g.addEdge(4, 5, 10); // e-f
    g.addEdge(5, 6, 2);  // f-g
    g.addEdge(6, 7, 1);  // g-h
    g.addEdge(6, 8, 6);  // g-i
    g.addEdge(7, 8, 7);  // h-i

    Prim prim;
    prim.primsMST(g);

    return 0;
}
