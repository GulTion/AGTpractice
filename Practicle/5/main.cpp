#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <fstream>
#include <cstddef>
#include "graph_list.h"
#include "euler_tour.h"


void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void task1_eulerianCheck(GraphList* graph) {
    std::cout << "\n--- Task 1: Check if Graph is Eulerian or Semi-Eulerian ---\n";

    // Get input from the user for the graph structure
    int numEdges;
    std::cout << "Enter the number of edges: ";
    std::cin >> numEdges;
    clearInputBuffer();

    int u, v, w;
    for (int i = 0; i < numEdges; ++i) {
        std::cout << "Enter edge " << i + 1 << " (from to weight): ";
        std::cin >> u >> v >> w;
        addEdge(graph, u, v, w);
        addEdge(graph, v, u, w);
    }

    if (isEulerian(graph)) {
        std::cout << "The graph is Eulerian.\n";
    } else if (isSemiEulerian(graph)) {
        std::cout << "The graph is Semi-Eulerian.\n";
    } else {
        std::cout << "The graph is not Eulerian or Semi-Eulerian.\n";
    }
}

void task2_hierholzer(GraphList& graph) {
    std::cout << "\n--- Task 2: Implement Hierholzer's Algorithm for Euler Tour ---\n";

    
    std::vector<int> tour = findEulerTour(&graph);

    if (!tour.empty()) {
        std::cout << "Euler Tour: ";
        for (int i = tour.size() - 1; i >= 0; --i) {
            std::cout << tour[i] << (i == 0 ? "" : " -> ");
        }
        std::cout << std::endl;
    } else {
        std::cout << "No Euler Tour exists.\n";
    }
}

void task3_visualizeEulerTour(GraphList& graph) {
    std::cout << "\n--- Task 3: Visualize Euler Tour ---" << std::endl;
    std::ofstream edgeFile("graph_edges_euler.txt");
    if (!edgeFile.is_open()) {
        std::cerr << "Error: Unable to open graph_edges_euler.txt for writing\n";
        return;
    }

    std::vector<Edge> edges = getEdgesList(&graph);
    for (const auto& edge : edges) {
        edgeFile << edge.from << " " << edge.to << " " << edge.weight << " 0\n"; // 0 indicates a regular edge
    }

    std::vector<int> eulerTour = findEulerTour(&graph);
    if (!eulerTour.empty()) {
        for (size_t i = 0; i < eulerTour.size() - 1; ++i) {
            edgeFile << eulerTour[i] << " " << eulerTour[i+1] << " 1 1\n"; // 1 indicates an Euler tour edge
        }
    }

    edgeFile.close();

    std::string pythonCommand = "python visualize_graph_euler.py";
    int result = std::system(pythonCommand.c_str());
    if (result != 0) {
        std::cerr << "Error: Failed to execute Python script. Error code: " << result << std::endl;
    } else {
        std::cout << "Graph and Euler Tour visualized using Python.\n";
    }
}

int main() {
    int numVertices = 6; 
    GraphList listGraph = *createGraph();
    for (int i = 0; i < numVertices; ++i) {
        addVertex(&listGraph, i);
    }
   
    clearInputBuffer();

    int choice = 0;
    while (choice != 4) {
        std::cout << "\nExperiment 5 Menu:\n";
        std::cout << "1. Check for Eulerian/Semi-Eulerian Property\n";
        std::cout << "2. Find and Print Euler Tour (Hierholzer's Algorithm)\n";
        std::cout << "3. Visualize Euler Tour\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                task1_eulerianCheck(&listGraph);
                break;
            case 2:
                task2_hierholzer(listGraph);
                break;
            case 3:
               task3_visualizeEulerTour(listGraph);
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
