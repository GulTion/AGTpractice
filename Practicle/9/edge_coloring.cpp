#include <bits/stdc++.h>
#include "edge_coloring.h"
#include "graph_list.h"
#include "vertex_coloring.h"
using namespace std;



map<pair<int, int>, int> VizingEdgeColoring(GraphList *graph) {
    int N = graph->numVertices;


    unordered_map<int, vector<int>> g = linkToList(graph);
    vector<Edge> edges = getEdgesList(graph);
    map<pair<int, int>, int> edgeColors;

    for (const Edge& e : edges) {
        unordered_set<int> neighborColors;

        for (int neighbor : g[e.u]) {
            if (edgeColors.find({min(e.u, neighbor), max(e.u, neighbor)}) != edgeColors.end()) {
                neighborColors.insert(edgeColors[{min(e.u, neighbor), max(e.u, neighbor)}]);
            }
        }

        for (int neighbor : g[e.v]) {
            if (edgeColors.find({min(e.v, neighbor), max(e.v, neighbor)}) != edgeColors.end()) {
                neighborColors.insert(edgeColors[{min(e.v, neighbor), max(e.v, neighbor)}]);
            }
        }

        int color = 0;
        while (neighborColors.find(color) != neighborColors.end()) {
            color++;
        }

        edgeColors[{min(e.u, e.v), max(e.u, e.v)}] = color;
    }

    return edgeColors;
}
