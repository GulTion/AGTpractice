#include<bits/stdc++.h>
#include "graph_list.h"
#include "vertex_coloring.h"
#include "edge_coloring.h"
using namespace std;

int main(){
	freopen("input.txt", "r", stdin); 
	int N,E,u,v;
	cin>> N >> E;
	GraphList *graph=createGraph();
	for(int v=0;v<N;++v) addVertex(graph, v);
	for(int e=0;e<E;++e){
		cin>>u>>v;
		addEdge(graph, u,v,0);
		addEdge(graph, v,u,0);
	}
	
	vector<int> colors;
	// task 1
	cout<<"Chromatic Number (using Greedy): "<<greedyVertexColoring(graph, colors)<<endl;
	for(int i=0;i<N;i++) {
		cout<<"V: "<<i<<" color: "<<colors[i]<<endl;
	}
	cout<<endl;
	
	// task 2
	cout<<"Chromatic Number (using BackTracking): "<<vertexColoring(graph, colors)<<endl;
	for(int i=0;i<N;i++) {
		cout<<"V: "<<i<<" color: "<<colors[i]<<endl;
	}
	
	cout<<endl;
	vector<Edge> edges = getEdgesList(graph);
    map<pair<int, int>, int> edgeColors = VizingEdgeColoring(graph);
    set<int> colors_index;
	for(Edge e:edges){
		colors_index.insert(edgeColors[{e.u, e.v}]);
	}
	cout<<"Chromatic Index (using Vizing): "<<colors_index.size()<<endl;
	
	for(Edge e:edges){
		cout << e.u<<"->"<<e.v<<" color: "<<(edgeColors[{e.u, e.v}])<<endl;
	}
	
	
	return 0;
}