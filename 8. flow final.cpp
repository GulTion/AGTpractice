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
int capacity;
int flow;
ArcNode(int _w):node{nullptr}, next{nullptr}, capacity{_w}, flow{0}{};
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

void addEdge(int u, int v, int w){
Node * src = getNode(u);
Node * dest = getNode(v);

ArcNode * arc1 = new ArcNode(w);
arc1->next = src->arc;
src->arc = arc1;
arc1->node = dest;
++E;
}

Node * getNode(int u){
Node * p=head;
while(p&&p->data!=u) p=p->next;
return p;
}



void reset(){
Node * p=head;
while(p){
p->vis = false;
p->parent = nullptr;
p=p->next;
}
}

};

ArcNode * getEdge(Node * u, Node *v){
	ArcNode * arc=u->arc;
	while(arc&&arc->node!=v){
		arc=arc->next;
	}
	
	return arc;
}

bool bfs(Graph * g, Node * s, Node * t){
	g->reset();
	
	queue<Node *> q;
	q.push(s);
	while(!q.empty()){
		Node * node = q.front();q.pop();
		node->vis = true;
		ArcNode * arc = node->arc;
		while(arc){
			Node * nbr = arc->node;
			if(!nbr->vis && arc->flow<arc->capacity){
				nbr->parent = node;
				if(nbr==t) return true;
				q.push(nbr);
			}
			arc=arc->next;
		}
	}
	return false;

}

int getFlow(Node * s, Node * t){
	int flow=INT_MAX;
	Node * p=t;	
	while(p!=s){
		Node * parent = p->parent;
		ArcNode * arc = getEdge(parent, p);
		flow=min(flow, arc->capacity-arc->flow);
		
		p=parent;
	}
	
	return flow;
}

void updateflow(Node * s, Node *t,int flow){
	Node * p=t;	
	while(p!=s){
		Node * parent = p->parent;
		ArcNode * arc = getEdge(parent, p);
		arc->flow+=flow;
		p=parent;
	}
}
// flow(bfs)
// updateflow
// maxflow

int maxFlow(Graph * g, Node * s, Node * t){
	int mxflow = 0, flow;
	while(bfs(g, s, t)){
		flow = getFlow(s, t);
		if(flow<=0) break;
		updateflow(s, t, flow);
		mxflow+=flow;
	}

	return mxflow;
}




int main() {
    Graph *g = new Graph();
    for (int i = 1; i <= 6; ++i) g->addNode(i);

    g->addEdge(1, 2, 16);
    g->addEdge(1, 3, 13);
    g->addEdge(2, 3, 10);
    g->addEdge(3, 2, 4);
    g->addEdge(2, 4, 12);
    g->addEdge(4, 3, 9);
    g->addEdge(3, 5, 14);
    g->addEdge(5, 4, 7);
    g->addEdge(4, 6, 20);
    g->addEdge(5, 6, 4);

    Node *s = g->getNode(1);
    Node *t = g->getNode(6);

    cout << "Max Flow: " << maxFlow(g, s, t) << endl;

    return 0;
}



