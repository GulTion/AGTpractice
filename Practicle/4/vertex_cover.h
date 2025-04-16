#ifndef VERTEX_COVER_H
#define VERTEX_COVER_H

#include "graph_matrix.h"
#include "graph_list.h"
#include <vector>

// Function to compute an approximate vertex cover using the adjacency matrix
std::vector<int> approxVertexCoverMatrix(const GraphMatrix& graph);

// Function to compute an approximate vertex cover using the linked list
std::vector<int> approxVertexCoverList(GraphList& graph);

#endif