#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>
#include "graph_list.h"
#include "graph_matrix.h"

using namespace std;

struct FlowEdge {
    int to;
    int capacity;
    int flow;
};

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

int fordFulkerson(vector<vector<FlowEdge>>& adjList, int s, int t, bool useDFS = false) {
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

int main() {
    GraphList* graph = createGraph();
    addVertex(graph, 0);
    addVertex(graph, 1);
    addVertex(graph, 2);
    addVertex(graph, 3);
    addVertex(graph, 4);
    addVertex(graph, 5);
    addEdge(graph, 0, 1, 8);
    addEdge(graph, 0, 3, 3);
    addEdge(graph, 1, 2, 9);
    addEdge(graph, 4, 3, 4);
    addEdge(graph, 4, 2, 7);
    addEdge(graph, 2, 5, 2);
    addEdge(graph, 3, 5, 5);
    vector<vector<FlowEdge>> flowNetwork = convertToFlowNetwork(graph);
    displayResidualGraph(flowNetwork);
    int source = 0;
    int sink = 5;
    int maxFlowBFS = fordFulkerson(flowNetwork, source, sink);
    cout << "Maximum Flow (BFS): " << maxFlowBFS << endl;
    flowNetwork = convertToFlowNetwork(graph);
    displayResidualGraph(flowNetwork);
    int maxFlowDFS = fordFulkerson(flowNetwork, source, sink, true);
    cout << "Maximum Flow (DFS): " << maxFlowDFS << endl;
    GraphList* userGraph = createGraph();
    int numNodes, numEdges;
    cout << "Enter the number of nodes: ";
    cin >> numNodes;
    for (int i = 0; i < numNodes; ++i) {
        addVertex(userGraph, i);
    }
    cout << "Enter the number of edges: ";
    cin >> numEdges;
    cout << "Enter the edges (from, to, capacity):" << endl;
    for (int i = 0; i < numEdges; ++i) {
        int u, v, cap;
        cin >> u >> v >> cap;
        addEdge(userGraph, u, v, cap);
    }
    vector<vector<FlowEdge>> userFlowNetwork = convertToFlowNetwork(userGraph);
    displayResidualGraph(userFlowNetwork);
    int userSource, userSink;
    cout << "Enter the source node: ";
    cin >> userSource;
    cout << "Enter the sink node: ";
    cin >> userSink;
    int userMaxFlowBFS = fordFulkerson(userFlowNetwork, userSource, userSink);
    cout << "Maximum Flow (BFS, User Input): " << userMaxFlowBFS << endl;
    return 0;
}

