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

set<int> approx_vertex_cover(Graph *g) {
    vector<Edge> edgeList = g->getEdges();
    set<Edge> edges(edgeList.begin(), edgeList.end());
    set<int> cover;

    while (!edges.empty()) {
        Edge e = *edges.begin();
        auto [u, v] = e;
        cover.insert(u);
        cover.insert(v);

        // Remove all edges incident to u or v
        set<Edge> toRemove;
        for (const Edge& e2 : edges) {
            if (e2.u == u || e2.v == u || e2.u == v || e2.v == v)
                toRemove.insert(e2);
        }
        for (const Edge& e2 : toRemove) {
            edges.erase(e2);
        }
    }

    return cover;
}

void printSet(const set<int>& s) {
    for (int v : s)
        cout << v << endl;
}

int main() {
    Graph *g = new Graph();
    for (int i = 0; i < 4; i++) g->addNode(i);

    g->addEdge(0, 1, 5);
    g->addEdge(3, 1, 15);
    g->addEdge(2, 1, 10);
    g->addEdge(0, 2, 8);
    g->addEdge(2, 3, 20);

    printSet(approx_vertex_cover(g));

    return 0;
}

