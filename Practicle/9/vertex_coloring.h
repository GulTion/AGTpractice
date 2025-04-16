#ifndef VERTEX_COLORING_H
#define VERTEX_COLORING_H
#include <vector>
#include"graph_list.h"
using namespace std;

	unordered_map<int, vector<int>> linkToList(GraphList *graph);
	int greedyVertexColoring(GraphList *graph, vector<int> &colors);
	int vertexColoring(GraphList *graph, vector<int> &colors);

#endif