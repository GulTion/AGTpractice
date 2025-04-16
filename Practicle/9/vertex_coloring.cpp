#include "graph_list.h"
#include <bits/stdc++.h>
using namespace std;

unordered_map<int, vector<int>> linkToList(GraphList *graph) {
    unordered_map<int, vector<int>> g;
    vector<Edge> edges = getEdgesList(graph);

    for (Edge e : edges) {
        g[e.u].push_back(e.v);
        g[e.v].push_back(e.u);
    }

    return g;
}

int greedyVertexColoring(GraphList *graph, vector<int> &colors) {
    int N = graph->numVertices;
    colors.assign(N, -1);

    unordered_map<int, vector<int>> g = linkToList(graph);

    int maxColor = 0;

    for (int node = 0; node < N; ++node) {
        unordered_set<int> neighborColors;
        
        for (int neighbor : g[node]) {
            if (colors[neighbor] != -1) {
                neighborColors.insert(colors[neighbor]);
            }
        }

        int color = 0;
        while (neighborColors.find(color) != neighborColors.end()) {
            color++;
        }

        colors[node] = color;
        maxColor = max(maxColor, color);
    }

    return maxColor + 1;
}

bool isSafe(int node, int color, vector<int> &colors, unordered_map<int, vector<int>> &g) {
    for (int neighbor : g[node]) {
        if (colors[neighbor] == color) {
            return false;
        }
    }
    return true;
}

bool graphColoringUtil(int node, int m, vector<int> &colors, unordered_map<int, vector<int>> &g) {
    int N = g.size();
    if (node == N) {
        return true;
    }

    for (int color = 0; color < m; ++color) {
        if (isSafe(node, color, colors, g)) {
            colors[node] = color;
            if (graphColoringUtil(node + 1, m, colors, g)) {
                return true;
            }
            colors[node] = -1;
        }
    }
    return false;
}

int vertexColoring(GraphList *graph, vector<int> &colors) {
    int N = graph->numVertices;
    unordered_map<int, vector<int>> g = linkToList(graph);

    for (int m = 1; m <= N; ++m) {
        colors.assign(N, -1);
        if (graphColoringUtil(0, m, colors, g)) {
            return m;
        }
    }

    return N; 
}
