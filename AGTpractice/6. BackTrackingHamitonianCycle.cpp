#include<bits/stdc++.h>
using namespace std;
struct ArcNode;
struct Node{
    int data;
    Node *next;
    Node * parent;
    bool vis;
    struct ArcNode *arc; // Missing struct keyword
    Node(int v) : data{v}, next{nullptr}, arc{nullptr}, vis{false}, parent{nullptr} {};
};

struct ArcNode{
    Node *node;
    ArcNode *next;
    ArcNode() : node{nullptr}, next{nullptr} {};
};

struct Graph{
    Node *head;
    int V;
    Graph() : head{nullptr}, V{0} {};

    void addNode(int v){
        Node *node = new Node(v); // Missing parameter v
        node->next = head;
        head = node;
        V++; // Incorrect: cout++ should be count++
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
    bool backTracking(Node * node, Node * start, int count){
    	node->vis = true;
	if(count==V){
		ArcNode * arc = node->arc;
		bool isConnected = false;
		while(arc){
			if(arc->node==start) {isConnected=true;break;}
			arc=arc->next;
		}
		
		if(isConnected){
			start->parent=node;
			return true;
		}else{
		node->vis = false;
		return false;
		}
	}
	
	
	ArcNode * arc = node->arc;
	while(arc){
	Node * next_node = arc->node;
	if(!next_node->vis){
		next_node->parent =node;
		if(backTracking(next_node, start, count+1)) return true;
		next_node->parent = nullptr;
		
	}
	
	arc=arc->next;
	}
	node->vis=false;

	return false;
}
};

int main(){
    Graph *g = new Graph();
    g->addNode(1);
    g->addNode(2);
    g->addNode(3);
    g->addNode(4);
    g->addNode(5);
    
    g->addEdge(1, 2);
    g->addEdge(1, 3);
    g->addEdge(2, 3);
    g->addEdge(3, 4);
    g->addEdge(3, 5);
    g->addEdge(4, 5);
    g->addEdge(2, 4);
   

    
if(g->backTracking(g->head, g->head, 1)){
    Node* p = g->head;
    do{
        cout<<(p->data)<<"->";
        p = p->parent;
    }while(p&&p!=g->head);
 
    cout << g->head->data << endl; // Complete cycle
} else {
    cout << "No Hamiltonian cycle found\n";
}

    return 0;
}
