#ifndef EULER_TOUR_H
#define EULER_TOUR_H

#include "graph_list.h"
#include <vector>


bool isEulerian(GraphList* graph);
bool isSemiEulerian(GraphList* graph);
int getDegree(GraphList* graph, int v);
void DFS(GraphList* graph, int v, std::vector<bool>& visited);
bool isConnected(GraphList* graph);
std::vector<int> findEulerTour(GraphList* graph);

#endif
