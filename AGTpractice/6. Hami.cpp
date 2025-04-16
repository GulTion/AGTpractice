#include<bits/stdc++.h>
using namespace std;
struct ArcNode;
struct Node{
int data;
int key;
bool vis;
Node * parent;
Node * next;
ArcNode * arc;
Node(int d):data{d}, key{INT_MAX}, parent{nullptr}, next{nullptr}, arc{nullptr}, vis{false}{};
};

struct ArcNode{
Node * node;
ArcNode * next;
ArcNode * bhai;
int w;
ArcNode():node{nullptr}, next{nullptr}, bhai{nullptr}, w{0}{};
};


struct Graph{
Node * head;
int V, E;
Graph():head{nullptr}, V{0},E{0}{};

void addNode(int x){
Node * node = new Node(x);
node->next = head;
head = node;
++V;
}

void addEdge(int u, int v){
Node * src = getNode(u);
Node * dest = getNode(v);

ArcNode * arc1 = new ArcNode();
arc1->next = src->arc;
src->arc = arc1;
arc1->node = dest;

ArcNode * arc2 = new ArcNode();
arc2->next = dest->arc;
dest->arc = arc2;
arc2->node = src;

arc1->bhai = arc2;
arc2->bhai = arc1;
++E;
}

Node * getNode(int u){
Node * p=head;
while(p&&p->data!=u) p=p->next;
return p;
}

};

bool backt(Graph *g, Node * curr, int V, Node * start){
// base condition
	curr->vis=true;
	if(g->V==V){
	bool isConn = false;
	ArcNode * arc = curr->arc;
	while(arc){
		if(arc->node==start){
		isConn = true;
		break;
		}
		arc=arc->next;
	}
	
	if(isConn){
		start->parent = curr;
		return true;
	}else{
		curr->vis=false;
		curr->parent = nullptr;
		return false;
	}

	}
	
	ArcNode * arc=curr->arc;
	//choice
	while(arc){
		Node * next_node = arc->node;
		//issafe
		if(!next_node->vis){
			next_node->vis = true;
			next_node->parent = curr;
			//recur
			if(backt(g, next_node, V+1, start)) return true;
			next_node->parent = nullptr;
			
		}
		arc=arc->next;
	}
	
	curr->vis=false;
	return false;


//backtracking

}

bool hami(Graph *g,Node * start){
return backt(g, start, 1, start);
}

void printhami(Node * start){
vector<int> path;
    Node * p=start;
    	do{
    	path.push_back(p->data);
    	p=p->parent;
    	
    	}while(p&&p!=start);
    	
    	path.push_back(start->data);
    	reverse(path.begin(), path.end());
    	
    	for(int i:path)cout <<i<<" ";

}
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
    
    Node * start = g->getNode(1);
    if(hami(g, start)){
    	printhami(start);
    }


return 0;
}

