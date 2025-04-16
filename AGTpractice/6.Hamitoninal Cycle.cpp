#include<bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    Node *next;
    bool vis;
    struct ArcNode *arc; // Missing struct keyword
    Node(int v) : data{v}, next{nullptr}, arc{nullptr}, vis{false} {};
};

struct ArcNode{
    Node *node;
    ArcNode *next;
    ArcNode() : node{nullptr}, next{nullptr} {};
};

struct Graph{
    Node *head;
    int count;
    Graph() : head{nullptr}, count{0} {};

    void addNode(int v){
        Node *node = new Node(v); // Missing parameter v
        node->next = head;
        head = node;
        count++; // Incorrect: cout++ should be count++
    }

    void addEdge(int u, int v){
        Node *src = getNode(u);
        Node *dest = getNode(v);

        if (!src || !dest) return; // Ensure nodes exist before adding edges

        ArcNode *arc = new ArcNode();
        arc->node = dest;
        arc->next = src->arc;
        src->arc = arc;

        ArcNode *arc2 = new ArcNode();
        arc2->node = src;
        arc2->next = dest->arc;
        dest->arc = arc2;
    }

    Node *getNode(int u){
        Node *p = head;
        while (p && p->data != u) p = p->next;
        return p;
    }
};

bool findHCycleUtil(Graph *g, vector<Node *> &path){ // Fix vector type
    Node *curr = path.back();
    if (path.size() == g->count){
        Node *start = path[0];
        ArcNode *arc = curr->arc;
        while (arc){
            if (arc->node == start) return true;
            arc = arc->next;
        }
        return false;
    }
    
    ArcNode *arc = curr->arc;
    while (arc){
        if (!arc->node->vis){
            arc->node->vis = true;
            path.push_back(arc->node);
            if (findHCycleUtil(g, path)) return true; // Missing semicolon
            arc->node->vis = false;
            path.pop_back();
        }
        arc = arc->next;
    }
    return false;
}

void findHCycle(Graph *g){ // Return type should be void
    vector<Node *> path;
    if (!g->head) {
        cout << "Graph is empty" << endl;
        return;
    }
    path.push_back(g->head);
    g->head->vis = true;
    if (findHCycleUtil(g, path)){
        for (Node *node : path){
            cout << node->data << " ";
        }
        cout<<path[0]->data;
        cout << endl;
    } else {
        cout << "No Cycle Found" << endl;
    }
}

int main(){
    Graph g;
    g.addNode(1);
    g.addNode(2);
    g.addNode(3);
    g.addNode(4);
    g.addNode(5);
    
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);
   

    
    findHCycle(&g);
    
    return 0;
}
