#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string> // For to_string
#include <utility> // For pair

using namespace std;

struct ArcNode;

struct Node {
    int data;
    int color;
    Node * next;
    ArcNode * arc;
    Node(int x) : data(x), color(0), next(nullptr), arc(nullptr) {}
};

struct ArcNode {
    Node * node;
    ArcNode * next;
    ArcNode() : node(nullptr), next(nullptr) {}
};

struct Graph {
    Node * head;
    int V, E;
    Graph() : head(nullptr), V(0), E(0) {}

    void addNode(int x) {
        Node *p = new Node(x);
        p->next = head;
        head = p;
        V++;
    }

    Node* getNode(int u) {
        Node * p = head;
        while (p && p->data != u) {
            p = p->next;
        }
        return p;
    }

    void addEdge(int u, int v) {
        Node * src = getNode(u);
        Node * dest = getNode(v);

        ArcNode * arc1 = new ArcNode();
        arc1->node = dest;
        arc1->next = src->arc;
        src->arc = arc1;

        ArcNode * arc2 = new ArcNode();
        arc2->node = src;
        arc2->next = dest->arc;
        dest->arc = arc2;
        E++;
    }





    
    	bool iSafe(Node * n, int c){
    		ArcNode * arc=n->arc;
    		while(arc){
    		if(arc->node->color==c) return false;
    		arc=arc->next;
    		} 
    		
    		return true;
    	}
    	bool backtracking(Node * node){
    		if(node==nullptr) return true;
    		
    		for(int c=1;c<=V;c++){
    			if(iSafe(node, c)){
    				node->color = c;
    				if(backtracking(node->next)) return true;;
    				node->color = 0;
    			}
    		}
    		return false;
    		
    	}
	bool OptimalVertexColor(){

		return backtracking(head);
	}


};



int main() {
    Graph * g = new Graph();

    for (int i = 1; i <= 4; i++) g->addNode(i);

    g->addEdge(1, 2);
    g->addEdge(1, 3);
    g->addEdge(4, 2);
    g->addEdge(3, 2);



    
    if(g->OptimalVertexColor()){
           Node * p = g->head;
while(p){
cout<<(p->data)<<" : "<<(p->color)<<endl;
p=p->next;
}

    }
       
       


    return 0;
}
