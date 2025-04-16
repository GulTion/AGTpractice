#ifndef HAMILTONIAN_H
#define HAMILTONIAN_H

#include <vector>
#include "graph_list.h"

bool findHamiltonianCycle(GraphList* graph, int startVertex, std::vector<int>& cycle);
bool hasHamiltonianCycleConditions(GraphList* graph);
void printHamiltonianCycle(const std::vector<int>& cycle);
void visualizeHamiltonianCycle(GraphList& graph);

#endif