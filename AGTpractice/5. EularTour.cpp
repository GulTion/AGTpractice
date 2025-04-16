#include <bits/stdc++.h>
using namespace std;

struct ArcNode;
struct Edge {
    int u, v;
    Edge(int a, int b): u{a}, v{b} {}

    // Needed to store in set
    bool operator<(const Edge& e) const {
        return tie(u, v) < tie(e.u, e.v);
    }
};

struct Node {
    int data, key;
    bool inMST;
    Node *parent, *next;
    ArcNode *arc;

    Node(int d): data{d}, key{INT_MAX}, parent{nullptr}, next{nullptr}, arc{nullptr}, inMST{false} {}
};

struct ArcNode {
    Node *node;
    ArcNode *next, *bhai;
    int w;
    ArcNode(int _w): node{nullptr}, next{nullptr}, bhai{nullptr}, w{_w} {}
};

struct Graph {
    Node *head;
    int V, E;
    Graph(): head{nullptr}, V{0}, E{0} {}

    void addNode(int x) {
        Node *node = new Node(x);
        node->next = head;
        head = node;
        ++V;
    }

    void addEdge(int u, int v, int w) {
        Node *src = getNode(u);
        Node *dest = getNode(v);

        ArcNode *arc1 = new ArcNode(w);
        arc1->next = src->arc;
        src->arc = arc1;
        arc1->node = dest;

        ArcNode *arc2 = new ArcNode(w);
        arc2->next = dest->arc;
        dest->arc = arc2;
        arc2->node = src;

        arc1->bhai = arc2;
        arc2->bhai = arc1;
        ++E;
    }

    Node* getNode(int u) {
        Node *p = head;
        while (p && p->data != u) p = p->next;
        return p;
    }

    void reset() {
        Node *p = head;
        while (p) {
            p->parent = nullptr;
            p->key = INT_MAX;
            p->inMST = false;
            p = p->next;
        }
    }

    vector<Edge> getEdges() {
        vector<Edge> edges;
        Node *p = head;
        while (p) {
            ArcNode *arc = p->arc;
            while (arc) {
                if (arc->node->data < p->data)
                    edges.push_back({arc->node->data, p->data});
                arc = arc->next;
            }
            p = p->next;
        }
        return edges;
    }
};


void EularTour(Node * u, vector<int> & cir, set<ArcNode *> &vis){
	ArcNode * arc = u->arc;
	while(arc){
	if(vis.count(arc)==0&&vis.count(arc->bhai)==0){
	vis.insert(arc);
	vis.insert(arc->bhai);
	EularTour(arc->node, cir,  vis);
	}
	
	arc=arc->next;}
	
	cir.push_back(u->data);
}



int main() {
    Graph *g = new Graph();
    for (int i = 0; i < 6; i++) g->addNode(i);

    g->addEdge(0, 1, 0);
    g->addEdge(2, 1, 0);
    g->addEdge(2, 3, 0);
    g->addEdge(3, 1, 0);
    g->addEdge(4, 1, 0);
    g->addEdge(4, 5, 0);
    g->addEdge(0, 5, 0);

	vector<int> cir;
	set<ArcNode *> vis;
    EularTour(g->head, cir, vis);
    reverse(cir.begin(), cir.end());
    for(auto i:cir) cout<<i<<" ";

    return 0;
}
