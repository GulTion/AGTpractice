#include "hamiltonian.h"
#include <iostream>
#include <fstream>  
#include <cstdlib> 

using namespace std;


void printHamiltonianCycle(const vector<int>& cycle) {
    cout << "Hamiltonian Cycle: ";
    for (int vertex : cycle) {
        cout << vertex << " ";
    }
    cout << cycle[0] << endl; 
}


bool findHamiltonianCycleUtil(GraphList* graph, int v, vector<bool>& visited, vector<int>& path, int startVertex, vector<int>& cycle) {
    visited[v] = true;
    path.push_back(v);

    if (path.size() == graph->numVertices) {
        GraphNode* lastNode = findVertex(graph, v);
        if (lastNode) {
            ArcNode* arc = lastNode->arcptr;
            while (arc) {
                if (arc->dest == startVertex) {
                    cycle = path; 
                    return true;
                }
                arc = arc->nextarc;
            }
        }  
        visited[v] = false;
        path.pop_back();
        return false;
    }

    GraphNode* currentNode = findVertex(graph, v);
    if (currentNode) {
        ArcNode* arc = currentNode->arcptr;
        while (arc) {
            int nextVertex = arc->dest;
            if (!visited[nextVertex]) {
                if (findHamiltonianCycleUtil(graph, nextVertex, visited, path, startVertex, cycle)) {
                    return true;
                }
            }
            arc = arc->nextarc;
        }
    }

    visited[v] = false;
    path.pop_back();

    return false;
}


bool findHamiltonianCycle(GraphList* graph, int startVertex, vector<int>& cycle) {
    vector<bool> visited(graph->numVertices, false);
    vector<int> path;
    cycle.clear();

    if (findHamiltonianCycleUtil(graph, startVertex, visited, path, startVertex, cycle)) {
        printHamiltonianCycle(cycle);
        return true;
    }

    cout << "No Hamiltonian cycle exists." << endl;
    return false;
}

// Function to check basic conditions for Hamiltonian cycles:
// 1. Graph must be connected.
// 2. Each vertex must have a degree of at least 2.
bool hasHamiltonianCycleConditions(GraphList* graph) {
    if (!graph || graph->numVertices == 0) return false;

    //degree of at least 2
    GraphNode* current = graph->head;
    while (current) {
        int degree = 0;
        ArcNode* arc = current->arcptr;
        while (arc) {
            degree++;
            arc = arc->nextarc;
        }
        if (degree < 2) {
            cout << "Vertex " << current->info << " has degree less than 2." << endl;
            return false;
        }
        current = current->nextnode;
    }

    // connectivity check
    if (graph->numVertices > 1 && graph->head->arcptr == NULL)
    {
        cout << "Graph might not be connected (very basic check)." << endl;
        return false;
    }

    return true;
}


void visualizeHamiltonianCycle(GraphList& graph) {
    cout << "\n--- Visualizing Hamiltonian Cycle ---" << endl;
    ofstream edgeFile("graph_edges_hamiltonian.txt");
    if (!edgeFile.is_open()) {
        cerr << "Error: Unable to open graph_edges_hamiltonian.txt for writing\n";
        return;
    }

    vector<Edge> edges = getEdgesList(&graph);
    for (const auto& edge : edges) {
        edgeFile << edge.from << " " << edge.to << " " << edge.weight << " 0\n";
    }

    vector<int> hamiltonianCycle;
    if (findHamiltonianCycle(&graph, 0, hamiltonianCycle)) { 

        for (size_t i = 0; i < hamiltonianCycle.size() - 1; ++i) {
            edgeFile << hamiltonianCycle[i] << " " << hamiltonianCycle[i+1] << " 1 1\n";
        }
        edgeFile << hamiltonianCycle.back() << " " << hamiltonianCycle.front() << " 1 1\n"; 
    }

    edgeFile.close();

    string pythonCommand = "python visualize_graph_hamiltonian.py";
    int result = system(pythonCommand.c_str());
    if (result != 0) {
        cerr << "Error: Failed to execute Python script. Error code: " << result << endl;
    } else {
        cout << "Graph and Hamiltonian Cycle visualized using Python.\n";
    }
}