#include <stdio.h>
#include <stdlib.h>
#include "graph_list.h"
#include <iostream>
#include <vector>


ArcNode* createArcNode(int dest) {
    ArcNode* newNode = (ArcNode*)malloc(sizeof(ArcNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->dest = dest;
    newNode->weight = 0;
    newNode->nextarc = NULL;
    return newNode;
}

GraphNode* createGraphNode(int info) {
    GraphNode* newNode = (GraphNode*)malloc(sizeof(GraphNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->info = info;
    newNode->nextnode = NULL;
    newNode->arcptr = NULL;
    return newNode;
}


GraphList* createGraph() {
    GraphList* graph = (GraphList*)malloc(sizeof(GraphList));
    if (graph == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    graph->head = NULL;
    graph->numVertices = 0;
    return graph;
}

void addVertex(GraphList* graph, int info) {
    GraphNode* newNode = createGraphNode(info);
    if (graph->head == NULL) {
        graph->head = newNode;
    } else {
        GraphNode* temp = graph->head;
        while (temp->nextnode != NULL) {
            temp = temp->nextnode;
        }
        temp->nextnode = newNode;
    }
    graph->numVertices++;
}

GraphNode* findVertex(GraphList* graph, int info){
    GraphNode* temp = graph->head;
    while(temp != NULL){
        if (temp->info == info){
            return temp;
        }
        temp = temp->nextnode;
    }
    return NULL;

}


void addEdge(GraphList* graph, int src, int dest, int weight) {
    GraphNode* srcNode = findVertex(graph, src);

    if (srcNode == NULL ) {
       std::cout << "Source or destination vertex not found!\n";
        return;
    }

    ArcNode* newArc = createArcNode(dest);
   newArc->weight = weight;
  if (srcNode->arcptr == NULL) {
       srcNode->arcptr = newArc;
    } else {
        ArcNode* temp = srcNode->arcptr;
        while (temp->nextarc != NULL) {
           temp = temp->nextarc;
        }
        temp->nextarc = newArc;
   }
}

void displayAdjacencyList(GraphList* graph) {
    GraphNode* temp = graph->head;
    if (temp == NULL){
        printf("The graph is empty.\n");
        return;
    }
   printf("Adjacency List:\n");
    while (temp != NULL) {
        printf("%d: ", temp->info);
        ArcNode* arcTemp = temp->arcptr;
        while (arcTemp != NULL) {
           printf("%d -> ", arcTemp->dest);
           arcTemp = arcTemp->nextarc;
        }
        printf("NULL\n");
        temp = temp->nextnode;
   }
}
std::vector<Edge> getEdgesList(GraphList* graph) {
    std::vector<Edge> edges;
    GraphNode* temp = graph->head;
   while(temp)
    {
       ArcNode* current = temp->arcptr;
        while (current)
        {
            if (temp->info < current->dest)
               edges.push_back(Edge(temp->info, current->dest, current->weight));
           
            current = current->nextarc;
        }
        temp = temp->nextnode;
   }
   return edges;
}
