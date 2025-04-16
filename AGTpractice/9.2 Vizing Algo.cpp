#include<bits/stdc++.h>
using namespace std;
struct ArcNode;
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
    ArcNode *bhai;
    int color;
    ArcNode() : node{nullptr}, next{nullptr}, color{0}, bhai{nullptr} {};
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
        
        arc->bhai = arc2;
        arc2->bhai = arc;
    }

    Node *getNode(int u){
        Node *p = head;
        while (p && p->data != u) p = p->next;
        return p;
    }
};

set<int> getColors(Node * node){
	set<int> colors;
	ArcNode * arc=node->arc;
	while(arc){
	if(arc->color)
	colors.insert(arc->color);
	arc=arc->next;
	}
	
	return colors;
}

void Vizing(Graph *g){
	int max_degree=-1, degree;
	Node *head = g->head;
	Node * p = head;
	while(p){
		degree = 0;
		ArcNode * arc = p->arc;
		while(arc){++degree; arc=arc->next;}
		max_degree = max(degree, max_degree);
		p=p->next;	
	}
	
	set<int> colors;
	
	for(int i=1;i<=max_degree+1;i++){
		colors.insert(i);
	}
	
	p = head;
	while(p){
	
		ArcNode * arc = p->arc;
		while(arc){
		if(arc->node->data<p->data){
		set<int> used_u = getColors(p);
		set<int> used_v = getColors(arc->node);
		
		
		set<int> u_v_union;
		set_union(
		used_u.begin(), used_u.end(),
		used_v.begin(), used_v.end(),
		inserter(u_v_union, u_v_union.begin())
		);
		
		set<int> avail_colors;
		set_difference(
		colors.begin(), colors.end(),
		u_v_union.begin(), u_v_union.end(),
		inserter(avail_colors, avail_colors.begin())
		);
		
		if (!avail_colors.empty()) {
    		arc->color = *avail_colors.begin();
    		arc->bhai->color = arc->color;
		}}
		
		arc=arc->next;}
		p=p->next;	
	}
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
   
   Vizing(g);
   
   Node * p = g->head;
	while(p){
		ArcNode * arc = p->arc;
		while(arc){
		if(arc->node->data<p->data)
		cout<<p->data<<"("<<arc->color<<")"<<arc->node->data<<endl;
		
		arc=arc->next;}
		p=p->next;	
	}
   

return 0;
}











