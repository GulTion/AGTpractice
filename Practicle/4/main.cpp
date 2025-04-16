#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <fstream>
#include <cstddef>
#include "graph_matrix.h"
#include "graph_list.h"
#include "vertex_cover.h"
#include "set_cover.h"

void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void task1_adjacencyMatrix(GraphMatrix& graph) {
    std::cout << "\n--- Task 1: Adjacency Matrix Implementation (Predefined Edges from the image) ---" << std::endl;
    // Add predefined edges here (modify as needed)
        graph.addEdge(0, 1, 1); // a-b (weight is arbitrary for vertex cover)
        graph.addEdge(1, 2, 1); // b-c
        graph.addEdge(2, 3, 1); // c-d
        graph.addEdge(2, 4, 1); // c-e
        graph.addEdge(3, 5, 1); // d-f
        graph.addEdge(4, 5, 1); // e-f
        graph.addEdge(3, 6, 1); // d-g

        
    
    graph.printAdjacencyMatrix();
     std::vector<int> cover = approxVertexCoverMatrix(graph);
     std::cout << "Vertex Cover: ";
     for (int vertex : cover) {
         std::cout << vertex << " ";
    }
     std::cout << "\nSize of Vertex Cover: " << cover.size() << std::endl;
    std::cout << "Task 1 completed. Predefined edges added and Adjacency Matrix is printed.\n";
}



void task2_userGraphInput(GraphList& graph) {
    std::cout << "\n--- Task 2: User Input Graph (Linked List) and Vertex Cover Visualization ---" << std::endl;

    clearInputBuffer();

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

    std::cout << "Graph created with user input.\n";

    // Compute and print vertex cover using greedy algorithm
    std::vector<int> cover = approxVertexCoverList(graph);
    std::cout << "Greedy Vertex Cover: ";
    for (int vertex : cover) {
        std::cout << vertex << " ";
    }
    std::cout << "\nSize of Vertex Cover: " << cover.size() << std::endl;

    // Write graph data to file for visualization
    std::ofstream edgeFile("graph_edges_vc.txt");
    if (!edgeFile.is_open()) {
        std::cerr << "Error: Unable to open graph_edges_vc.txt for writing\n";
        return;
    }

    
    std::vector<Edge> edges = getEdgesList(&graph);
    for (const auto& edge : edges) {
        edgeFile << edge.from << " " << edge.to << " " << edge.weight << " 0\n"; 
    }

    
    for (int vertex : cover) {
        edgeFile << vertex << " " << vertex << " 0 1\n"; 
    }

    edgeFile.close();

    // Call the Python script for visualization
    std::string pythonCommand = "python visualize_graph 	_vc.py";
    int result = std::system(pythonCommand.c_str());
    if (result != 0) {
        std::cerr << "Error: Failed to execute Python script. Error code: " << result << std::endl;
    } else {
        std::cout << "Graph and Vertex Cover visualized using Python.\n";
    }
}

void task3_setCover() {
    std::cout << "\n--- Task 3: Greedy Set Cover ---" << std::endl;

    // Example usage (you can modify this with user input)
    std::set<int> U = {1, 2, 3, 4, 5};
    std::vector<std::set<int>> subsets = {{1, 2}, {2, 3, 4}, {4, 5}};

    std::vector<std::set<int>> cover = greedySetCover(U, subsets);

    std::cout << "Minimal Set Cover:\n";
    for (const auto& set : cover) {
        std::cout << "{ ";
        for (int element : set) {
            std::cout << element << " ";
        }
        std::cout << "}\n";
    }
}

int main() {
    int numVertices = 7;
    GraphMatrix matrixGraph(numVertices);
    GraphList listGraph = *createGraph();
    for (int i = 0; i < numVertices; ++i) {
           addVertex(&listGraph, i);
    }
    
    clearInputBuffer();
    
    int choice = 0;
    
    while (choice != 4) {
        std::cout << "\nExperiment 4 Menu:\n";
        std::cout << "1. Implement Adjacency Matrix (Predefined Edges from Image)\n";
        std::cout << "2. Create Graph from user input and visualize the vertex cover\n";
        std::cout << "3. Greedy Set Cover\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                task1_adjacencyMatrix(matrixGraph);
                break;
            case 2:
                task2_userGraphInput(listGraph);
                break;
            case 3:
                task3_setCover();
                break;
            case 4:
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
    
    return 0;
}