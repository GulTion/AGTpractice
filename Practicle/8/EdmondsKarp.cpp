#include "EdmondsKarp.h"
#include "graph_matrix.h"
#include<bits/stdc++.h>
#include "fordFulkerson.h"

using namespace std;
using namespace chrono;
// task 1
vector<int> shortestPath(GraphMatrix &g, int S, int D) {
    vector<vector<int>> adjm = g.getAdjacencyMatrix();
    int N = g.getNumVertices();

    vector<bool> visited(N, false);
    vector<int> parent(N, -1);
    vector<int> path;

    queue<int> q;
    q.push(S);
    visited[S] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        if (node == D) break;

        for (int j = 0; j < N; j++) {
            if (adjm[node][j] > 0 && !visited[j]) {
                q.push(j);
                visited[j] = true;
                parent[j] = node;
            }
        }
    }

    if (visited[D]) {
        for (int v = D; v != -1; v = parent[v]) path.push_back(v);
        reverse(path.begin(), path.end());
    }
//    for(int i:path) cout<<i<<" ";
    cout<<endl;

    return path;
}

// task 2
int residualGraphUpdate(GraphMatrix &g, vector<int> path, int S, int D) {
    vector<vector<int>> adjm = g.getAdjacencyMatrix();
    int bottleneck = INT_MAX;

    for (int i = 1; i < path.size(); i++) {
        int u = path[i - 1];
        int v = path[i];
        bottleneck = min(bottleneck, adjm[u][v]);
    }

    for (int i = path.size() - 1; i > 0; i--) {
        int u = path[i];
        int v = path[i - 1];
        
        g.addEdgeDirected(u,v,adjm[u][v] + bottleneck);
		g.addEdgeDirected(v,u,adjm[v][u] - bottleneck);        

    }
    
    return bottleneck;
}

int edmondsKarp(GraphMatrix &g, int S, int D) {
    int maxFlow = 0;

    while (true) {
        vector<int> path = shortestPath(g, S, D);
        if (path.empty()) break; 

        int bottleneck = residualGraphUpdate(g, path, S, D);
//        g.printAdjacencyMatrix();
    
        maxFlow += bottleneck;
    }

    return maxFlow;
}

void compareAlgorithms() {
    int N,E, u, v , w;cout<<"Number of Nodes and Edges: ";cin>>N>>E;
    
	GraphMatrix graph = GraphMatrix(N);
    vector<vector<FlowEdge>> adjList(N);
    
	for(int i=0;i<E;i++){
//		cout<<"Enter Edge (u, v, w): "; 
		cin>>u>>v>>w;
		graph.addEdgeDirected(u,v,w);
		 
		adjList[u].push_back({v, w, 0});
		
	}
	int S,D; 
//	cout<<"Enter S and D: "; 
	cin>>S>>D;

    

    // Measure execution time of Ford-Fulkerson with DFS
    auto start = chrono::steady_clock::now();


    int maxFlowDFS = fordFulkerson(adjList, S, D, true);
    auto end = chrono::steady_clock::now();
    
    auto  durationDFS = chrono::duration_cast<chrono::microseconds>(end - start);
    cout<<endl;
    cout << "Ford-Fulkerson using DFS max flow: " << maxFlowDFS << endl;
    cout << "Execution time Ford-Fulkerson: " << durationDFS.count() << " nanoseconds" << endl;

    // Measure execution time of Ford-Fulkerson with BFS (Edmonds-Karp)
    start = chrono::steady_clock::now();
	
    int maxFlowBFS = edmondsKarp(graph, S, D);
    end = chrono::steady_clock::now();
    auto  durationBFS = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Edmonds-Karp max flow: " << maxFlowBFS << endl;
    cout << "Execution time Edmonds-Karp: " << durationBFS.count() << " nanoseconds" << endl;
}