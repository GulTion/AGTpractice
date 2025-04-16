#include<bits/stdc++.h>
using namespace std;
struct ArcNode;
struct Node{
int data;
int key;
bool inMST;
Node * parent;
Node * next;
ArcNode * arc;
Node(int d):data{d}, key{INT_MAX}, parent{nullptr}, next{nullptr}, arc{nullptr}, inMST{false}{};
};

struct ArcNode{
Node * node;
ArcNode * next;
ArcNode * bhai;
int w;
ArcNode(int _w):node{nullptr}, next{nullptr}, bhai{nullptr}, w{_w}{};
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

ArcNode * arc2 = new ArcNode(w);
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

void reset(){
Node * p = head;
while(p){
p->parent = nullptr;
p->key = INT_MAX;
p->inMST = false;
p=p->next;
}
}
};



void MSTPrim(Graph *g, Node *r){
g->reset();
set<pair<int, int>> q;
r->key = 0;
Node * p=g->head;
while(p){
q.insert({p->key, p->data});
p=p->next;
}

while(!q.empty()){
auto p = *q.begin();
Node * node = g->getNode(p.second);
node->inMST = true;
q.erase(p);
ArcNode * arc = node->arc;
while(arc){
Node * nbr = arc->node;
if(!nbr->inMST && arc->w < nbr->key){
	nbr->parent = node;
	q.erase({nbr->key, nbr->data});
	nbr->key = arc->w;
	q.insert({nbr->key, nbr->data});
}
arc=arc->next;
}

}
}

void printMST(Graph *g){
    Node * node = g->head;
    while(node){
        
        if (node->parent) 
            cout << node->data << " -> " << node->parent->data;
       
        cout << endl;
        node = node->next;
    }
}



int main(){
Graph * g = new Graph();
for(int i=0;i<4;i++){g->addNode(i);}
g->addEdge(0,1,5);
g->addEdge(3,1,15);
g->addEdge(2,1,10);
g->addEdge(0,2,8);
g->addEdge(2,3,20);

MSTPrim(g, g->getNode(0));
printMST(g);

return 0;


};

