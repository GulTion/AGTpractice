#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "graph_matrix.h"
#include "graph_list.h"
#include <vector>

class Kruskal {
private:
    std::vector<Edge> findMSTHelper(std::vector<Edge>& edges, int numVertices);
public:
    Kruskal();
    std::vector<Edge> findMST(GraphMatrix& graph);
    std::vector<Edge> findMST(GraphList& graph);
};
#endif