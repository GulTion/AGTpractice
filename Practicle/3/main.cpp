#include <iostream>
#include "graph_matrix.h"
#include "kruskal.h"
#include <limits>
#include <string>
#include <sstream>
#include <fstream>
#include <cstddef>
#include "graph_list.h"

void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void task1_adjacencyMatrix(GraphMatrix& graph) {
    std::cout << "\n--- Task 1: Adjacency Matrix Implementation (Predefined Edges from the image) ---" << std::endl;
    // Add predefined edges here (modify as needed)
    graph.addEdge(4, 3, 9);
    graph.addEdge(4, 5, 10);
    graph.addEdge(3, 5, 14);
    graph.addEdge(3, 2, 7);
    graph.addEdge(2, 5, 4);
    graph.addEdge(2, 6, 2);
    graph.addEdge(2, 1, 8);
    graph.addEdge(6, 8, 6);
    graph.addEdge(5, 6, 2);
    graph.addEdge(8, 7, 1);
    graph.addEdge(8, 1, 7);
    graph.addEdge(7, 1, 11);
    graph.addEdge(7, 0, 8);
    graph.addEdge(1, 0, 4);
    
    graph.printAdjacencyMatrix();
    std::cout << "Task 1 completed. Predefined edges added and Adjacency Matrix is printed.\n";
}
    
void task2_cycleDetection(GraphMatrix& matrixGraph, GraphList& listGraph) {
    std::cout << "\n--- Task 2: Cycle Detection ---" << std::endl;

    Kruskal kruskal;
    std::vector<Edge> mstEdgesMatrix = kruskal.findMST(matrixGraph);
    std::cout << "Kruskal's Algorithm was executed on Adjacency Matrix, cycles are skipped.\n";
    std::vector<Edge> mstEdgesList = kruskal.findMST(listGraph);
    std::cout << "Kruskal's Algorithm was executed on Adjacency List, cycles are skipped.\n";
}
    
void task3_linkedListInput(GraphList& graph) {
    std::cout << "\n--- Task 3: Linked List Input and MST Computation (User Input Edges) ---" << std::endl;
       
        int u, v, w;
        
        std::cout << "Enter edges (from to weight), enter -1 -1 -1 to stop:\n";
        while (true) {
            std::cout << "Enter edge (from, to): ";
            std::cin >> u >> v;
           if (u == -1 && v == -1) {
                break;
            }
            std::cout << "Enter weight: ";
           std::cin >> w;
           addEdge(&graph, u, v, w);
        }
    
    
       Kruskal kruskal;
        std::vector<Edge> mstEdges = kruskal.findMST(graph);
        std::cout << "Edges in Minimum Spanning Tree:\n";
       for (const auto& edge : mstEdges) {
            std::cout << edge.from << " -- " << edge.weight << " -- " << edge.to << "\n";
        }
        displayAdjacencyList(&graph);
       std::cout << "Task 3 completed. MST computed and printed from user inputted edges using a linked list representation.\n";
}

void task4_visualizeGraph(GraphList& graph) {
    std::cout << "\n--- Task 4: Graph Visualization (Python with MST) ---" << std::endl;
        // 1. Prepare data file with edges and MST edges
           std::ofstream edgeFile("graph_edges.txt");
           if (!edgeFile.is_open()) {
                std::cerr << "Error: Unable to open graph_edges.txt for writing\n";
                return;
            }
    
        Kruskal kruskal;
       std::vector<Edge> mstEdges = kruskal.findMST(graph);
        std::vector<Edge> edges = getEdgesList(&graph);
        // Send all edges, along with the MST information.
       for (const auto& edge : edges) {
           bool isMST = false;
           for(const auto& mstEdge : mstEdges)
            {
                if((edge.from == mstEdge.from && edge.to == mstEdge.to) || (edge.to == mstEdge.from && edge.from == mstEdge.to))
                   isMST = true;
            }
            edgeFile << edge.from << " " << edge.to << " " << edge.weight << " " << isMST << "\n";
       }
       edgeFile.close();
        
         // 2. Call the python script
       std::string pythonCommand = "python visualize_graph.py";
        int result = std::system(pythonCommand.c_str());
        if (result != 0) {
             std::cerr << "Error: Failed to execute Python script. Error code: " << result << std::endl;
       } else {
           std::cout << "Graph and Minimum Spanning Tree visualized using Python.\n";
       }
}
    
    
int main() {
   int numVertices = 9;
    GraphMatrix matrixGraph(numVertices);
    GraphList listGraph = *createGraph();
    for (int i = 0; i < numVertices; ++i) {
           addVertex(&listGraph, i);
    }
    
    clearInputBuffer();
    
    int choice = 0;
    
    while (choice != 5) {
       std::cout << "\nMain Menu:\n";
        std::cout << "1. Implement Adjacency Matrix (Predefined Edges from Image)\n";
        std::cout << "2. Detect Cycles during edge selection\n";
       std::cout << "3. Input edges and weights and prepare Linked Representation to further compute the MST (User Input Edges)\n";
        std::cout << "4. Visualize the Graph (Python with MST)\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
       std::cin >> choice;
        
       switch (choice) {
            case 1:
                task1_adjacencyMatrix(matrixGraph);
               break;
            case 2:
               task2_cycleDetection(matrixGraph, listGraph);
                break;
           case 3:
               task3_linkedListInput(listGraph);
                break;
            case 4:
                task4_visualizeGraph(listGraph);
                break;
            case 5:
               std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
       }
   }
    
   return 0;
}