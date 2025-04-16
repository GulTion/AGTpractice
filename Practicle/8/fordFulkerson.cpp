#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>
#include "graph_list.h"
#include "fordFulkerson.h"

using namespace std;

vector<vector<FlowEdge>> convertToFlowNetwork(GraphList* graph) {
    int numNodes = graph->numVertices;
    vector<vector<FlowEdge>> adjList(numNodes);
    GraphNode* currentGraphNode = graph->head;
    while (currentGraphNode != NULL) {
        int u = currentGraphNode->info;
        ArcNode* currentArcNode = currentGraphNode->arcptr;
        while (currentArcNode != NULL) {
            int v = currentArcNode->dest;
            int capacity = currentArcNode->weight;
            adjList[u].push_back({v, capacity, 0});
            adjList[v].push_back({u, 0, 0});
            currentArcNode = currentArcNode->nextarc;
        }
        currentGraphNode = currentGraphNode->nextnode;
    }
    return adjList;
}

bool bfs(const vector<vector<FlowEdge>>& adjList, int s, int t, vector<int>& parent) {
    int numNodes = adjList.size();
    vector<bool> visited(numNodes, false);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const auto& edge : adjList[u]) {
            int v = edge.to;
            int residualCapacity = edge.capacity - edge.flow;
            if (!visited[v] && residualCapacity > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return visited[t];
}

bool dfs(const vector<vector<FlowEdge>>& adjList, int u, int t, vector<int>& parent, vector<bool>& visited) {
    if (u == t) return true;
    visited[u] = true;
    for (const auto& edge : adjList[u]) {
        int v = edge.to;
        int residualCapacity = edge.capacity - edge.flow;
        if (!visited[v] && residualCapacity > 0) {
            parent[v] = u;
            if (dfs(adjList, v, t, parent, visited)) return true;
        }
    }
    return false;
}

int fordFulkerson(vector<vector<FlowEdge>>& adjList, int s, int t, bool useDFS) {
    int numNodes = adjList.size();
    vector<int> parent(numNodes);
    int maxFlow = 0;
    vector<vector<FlowEdge>> residualGraph = adjList;
    vector<bool> visited(numNodes, false);
    while (true) {
        fill(parent.begin(), parent.end(), -1);
        fill(visited.begin(), visited.end(), false);
        bool pathFound;
        if (useDFS) pathFound = dfs(residualGraph, s, t, parent, visited);
        else pathFound = bfs(residualGraph, s, t, parent);
        if (!pathFound) break;
        int pathFlow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            for (auto& edge : residualGraph[u]) {
                if (edge.to == v) {
                    pathFlow = min(pathFlow, edge.capacity - edge.flow);
                    break;
                }
            }
        }
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            for (auto& edge : residualGraph[u]) {
                if (edge.to == v) {
                    edge.flow += pathFlow;
                    break;
                }
            }
            for (auto& edge : residualGraph[v]) {
                if (edge.to == u) {
                    edge.flow -= pathFlow;
                    break;
                }
            }
        }
        maxFlow += pathFlow;
    }
    return maxFlow;
}

void displayResidualGraph(const vector<vector<FlowEdge>>& adjList) {
    for (size_t u = 0; u < adjList.size(); ++u) {
        for (const auto& edge : adjList[u]) {
            if (edge.capacity > 0) {
                cout << u << " -> " << edge.to << ": " << edge.flow << "/" << edge.capacity << endl;
            }
        }
    }
}
