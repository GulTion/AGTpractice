#include<bits/stdc++.h>
using namespace std;
struct ArcNode;
struct Edge{
int w;
int u;
int v;
Edge(int _w,int _u,int _v):w{_w}, u{_u}, v{_v}{};
bool operator<(Edge e){
return w < e.w;
}
};
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
int w;
Node * node;
ArcNode * next;
ArcNode * bhai;
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

vector<Edge> getEdges(){
vector<Edge> edges;
Node * p=head;
while(p){
ArcNode * arc = p->arc;
while(arc){
if(arc->node->data<p->data) edges.push_back({arc->w, arc->node->data, p->data});
arc=arc->next;
}
p=p->next;
}

return edges;
}
};

struct DSU{
vector<int> arr;
DSU(int n){
arr.assign(n, -1);
for(int i=0;i<n;i++) arr[i]=i;

};
int find(int a){
if(arr[a]==a) return arr[a];
return arr[a] = find(arr[a]);
}
void merge(int a, int b){
a = find(a);
b = find(b);
arr[b]=a;
}
};

vector<Edge> Kru(Graph *g){
vector<Edge> res;
vector<Edge> edges = g->getEdges();
sort(edges.begin(), edges.end());

DSU *dsu = new DSU(g->V);

for(auto e:edges){
auto [w,u,v] = e;
if(dsu->find(u)!=dsu->find(v)){
res.push_back(e);
dsu->merge(u,v);
}

}

return res;
}

void printKru(vector<Edge> edges){
for(auto [w,u,v]:edges) cout<<u<<"-"<<w<<"->"<<v<<endl;
}


int main(){
Graph * g = new Graph();
for(int i=0;i<4;i++){g->addNode(i);}
g->addEdge(0,1,5);
g->addEdge(3,1,15);
g->addEdge(2,1,10);
g->addEdge(0,2,8);
g->addEdge(2,3,20);

Kru(g);
printKru(Kru(g));

return 0;


};


