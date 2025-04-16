#ifndef EDMONDSKARP_H
#define EDMONDSKARP_H
#include<vector>
#include "graph_matrix.h"
using namespace std;

vector<int> shortestPath(GraphMatrix &g, int S, int D);
int residualGraphUpdate(GraphMatrix &g, vector<int> path, int S, int D);
int edmondsKarp(GraphMatrix &g, int S, int D);
void compareAlgorithms();

#endif