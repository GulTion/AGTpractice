#ifndef FORDFULKERSON_H
#define FORDFULKERSON_H
#include <iostream> 
#include <vector>    
#include <queue>  
#include "graph_list.h"



struct FlowEdge {
    int to;
    int capacity;
    int flow;
};
bool dfs(const std::vector<std::vector<FlowEdge>>& adjList, int u, int t, std::vector<int>& parent, std::vector<bool>& visited);
int fordFulkerson(std::vector<std::vector<FlowEdge>>& adjList, int s, int t, bool useDFS = false);
void displayResidualGraph(const std::vector<std::vector<FlowEdge>>& adjList);
std::vector<std::vector<FlowEdge>> convertToFlowNetwork(GraphList* graph);

#endif 
