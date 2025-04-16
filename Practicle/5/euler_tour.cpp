#include "euler_tour.h"
#include "graph_list.h"
#include <iostream>
#include <stack>

int GraphList::getNumVertices(){
	return numVertices;
} 

int getDegree(GraphList* graph, int v) {
    GraphNode* temp = findVertex(graph, v);
   if (temp == NULL) return 0;
   int degree = 0;
   ArcNode* arcTemp = temp->arcptr;
    while (arcTemp != NULL) {
        degree++;
        arcTemp = arcTemp->nextarc;
    }
    return degree;
}

void DFS(GraphList* graph, int v, std::vector<bool>& visited) {
    visited[v] = true;
    GraphNode* vertexNode = findVertex(graph, v);
     if (vertexNode == NULL) return; 

   ArcNode* arcTemp = vertexNode->arcptr;
    while (arcTemp != NULL) {
        int adjacentVertex = arcTemp->dest;
        if (!visited[adjacentVertex]) DFS(graph, adjacentVertex, visited);
        arcTemp = arcTemp->nextarc;
    }
}

bool isConnected(GraphList* graph) {
    int numVertices = graph->numVertices;
    std::vector<bool> visited(numVertices, false);

   int startVertex = -1;
    for (int i = 0; i < numVertices; ++i) 
       if (getDegree(graph, i) > 0) {
           startVertex = i;
            break;
       }
    
    if (startVertex == -1) return true;
    
    DFS(graph, startVertex, visited);

    for (int i = 0; i < numVertices; ++i)
        if (!visited[i] && getDegree(graph, i) > 0) 
            return false;
            
    return true;
}

bool isEulerian(GraphList* graph) {
    if (!isConnected(graph)) {
    	std::cout<<"Not Connected"<<std::endl;
        return false;
    }

    for (int i = 0; i < graph->numVertices; ++i) 
	if (getDegree(graph, i) % 2 != 0) return false;
    
    return true;
}

bool isSemiEulerian(GraphList* graph) {
    if (!isConnected(graph)) {
        return false;
    }

    int oddDegreeCount = 0;
    for (int i = 0; i < graph->numVertices; ++i) {
        if (getDegree(graph, i) % 2 != 0) {
           oddDegreeCount++;
        }
    }
    return (oddDegreeCount == 2);
}

std::vector<int> findEulerTour(GraphList* graph) {
    std::vector<int> circuit;
    if (!isEulerian(graph) && !isSemiEulerian(graph)) {
        std::cerr << "Graph is not Eulerian or Semi-Eulerian.\n";
        return circuit;
    }

    std::stack<int> currPath;
    std::vector<int> finalCircuit;

    int numEdges = 0;
    GraphNode* temp = graph->head;
    while(temp != NULL){
      ArcNode* current = temp->arcptr;
         while (current != NULL)
        {
            numEdges++;
           current = current->nextarc;
        }
        temp = temp->nextnode;
   }
   std::vector<std::vector<int>> adjList(graph->numVertices);
    temp = graph->head;
    while(temp != NULL){
       ArcNode* current = temp->arcptr;
       while (current != NULL)
       {
          adjList[temp->info].push_back(current->dest);
          current = current->nextarc;
       }
       temp = temp->nextnode;
   }
   
   int currentVertex = 0; 
    currPath.push(currentVertex);

    while (!currPath.empty()) {
        if (adjList[currentVertex].size() > 0) {
            currPath.push(currentVertex);
          int nextVertex = adjList[currentVertex].back();
            adjList[currentVertex].pop_back();
           
            for (int i = 0; i < adjList[nextVertex].size(); ++i) {
               if (adjList[nextVertex][i] == currentVertex) {
                   adjList[nextVertex].erase(adjList[nextVertex].begin() + i);
                    break;
                }
            }
           currentVertex = nextVertex;
        } else {
            finalCircuit.push_back(currentVertex);
            currentVertex = currPath.top();
            currPath.pop();
       }
   }

    return finalCircuit;
}
