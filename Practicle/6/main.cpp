#include <iostream>
#include <vector>
#include "graph_list.h"
#include "graph_matrix.h"
#include "hamiltonian.h"

using namespace std;

int main() {
    cout << "Task 1: Find Hamiltonian cycles in the given graphs" << endl;

    GraphList* graph1 = createGraph();
    addVertex(graph1, 0); // A
    addVertex(graph1, 1); // B
    addVertex(graph1, 2); // C
    addVertex(graph1, 3); // D
    addVertex(graph1, 4); // E

    addEdgeUndirected(graph1, 0, 1, 1); // A-B
    addEdgeUndirected(graph1, 0, 3, 1); // A-D
    addEdgeUndirected(graph1, 1, 2, 1); // B-C
    addEdgeUndirected(graph1, 2, 4, 1); // C-E
    addEdgeUndirected(graph1, 3, 4, 1); // D-E
    addEdgeUndirected(graph1, 2, 3, 1); // C-D

    cout << "Graph 1:" << endl;
    displayAdjacencyList(graph1);
    vector<int> cycle1;
    findHamiltonianCycle(graph1, 0, cycle1); // Start from vertex A (0)




    GraphList* graph2 = createGraph();
    addVertex(graph2, 0); // A
    addVertex(graph2, 1); // B
    addVertex(graph2, 2); // C
    addVertex(graph2, 3); // D
    addVertex(graph2, 4); // E

    addEdgeUndirected(graph2, 4, 0, 1); // E-A
    addEdgeUndirected(graph2, 0, 3, 1); // A-D
    addEdgeUndirected(graph2, 3, 2, 1); // D-C
    addEdgeUndirected(graph2, 2, 1, 1); // C-B
    addEdgeUndirected(graph2, 0, 1, 1); // A-B


    cout << "\nGraph 2:" << endl;
    displayAdjacencyList(graph2);
    vector<int> cycle2;
    findHamiltonianCycle(graph2, 4,cycle2);


    cout << "\nTask 2: User input graph" << endl;
    int numVertices;
    cout << "Enter the number of vertices in the graph: ";
    cin >> numVertices;

    GraphList* userGraph = createGraph();
    for (int i = 0; i < numVertices; ++i) {
        addVertex(userGraph, i); 
    }

    int numEdges;
    cout << "Enter the number of edges in the graph: ";
    cin >> numEdges;

    cout << "Enter the edges (source destination weight):\n";
    for (int i = 0; i < numEdges; ++i) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        addEdgeUndirected(userGraph, src, dest, weight);
    }

    cout << "User Graph:" << endl;
    displayAdjacencyList(userGraph);

    if (hasHamiltonianCycleConditions(userGraph)) {
        cout << "The graph satisfies basic conditions for Hamiltonian cycles." << endl;
    } else {
        cout << "The graph does not satisfy basic conditions for Hamiltonian cycles." << endl;
    }
    visualizeHamiltonianCycle(*userGraph);

    // Task 3:  Extend your implementation to visualize the graph and highlight the Hamiltonian cycle if it exists.
    cout << "\nTask 3: Visualization is  integrated using external python script " << endl;

    return 0;
}