#include <bits/stdc++.h>
using namespace std;

struct ArcNode;
struct Node {
    int data;
    Node *next;
    bool vis;
    Node *parent;
    struct ArcNode *arc;
    Node(int v) : data{v}, next{nullptr}, arc{nullptr}, vis{false}, parent{nullptr} {}
};

struct ArcNode {
    Node *node;
    ArcNode *next;
    int flow;
    int capacity;
    ArcNode() : node{nullptr}, next{nullptr}, flow{0}, capacity{0} {}
};

struct Graph {
    Node *head;
    int count;
    Graph() : head{nullptr}, count{0} {};

    void addNode(int v) {
        Node *node = new Node(v);
        node->next = head;
        head = node;
        count++;
    }

    void addEdge(int u, int v, int w) {
        Node *src = getNode(u);
        Node *dest = getNode(v);

        if (!src || !dest) return;

        ArcNode *arc = new ArcNode();
        arc->node = dest;
        arc->next = src->arc;
        arc->capacity = w;
        arc->flow = 0;
        src->arc = arc;
    }

    Node *getNode(int u) {
        Node *p = head;
        while (p && p->data != u) p = p->next;
        return p;
    }
};

ArcNode* getEdge(Node *u, Node *v) {
    ArcNode *arc = u->arc;
    while (arc && arc->node != v) arc = arc->next;
    return arc;
}

bool bfs(Graph *g, Node *s, Node *t) {
    for (Node *p = g->head; p; p = p->next) {
        p->vis = false;
        p->parent = nullptr;
    }

    queue<Node *> q;
    q.push(s);
    s->vis = true;

    while (!q.empty()) {
        Node *node = q.front(); q.pop();
        ArcNode *arc = node->arc;
        while (arc) {
            Node *nbr = arc->node;
            if (!nbr->vis && arc->flow < arc->capacity) {
                nbr->vis = true;
                nbr->parent = node;
                if (nbr == t) return true;
                q.push(nbr);
            }
            arc = arc->next;
        }
    }

    return false;
}

int getMinFlow(Node *s, Node *t) {
    int flow = INT_MAX;
    Node *p = t;
    while (p != s) {
        Node *prv = p->parent;
        ArcNode *arc = getEdge(prv, p);
        flow = min(flow, arc->capacity - arc->flow);
        p = prv;
    }
    return flow;
}

void updateFlow(Node *s, Node *t, int flow) {
    Node *p = t;
    while (p != s) {
        Node *prv = p->parent;
        ArcNode *arc = getEdge(prv, p);
        arc->flow += flow;
        p = prv;
    }
}

int maxFlow(Graph *g, Node *s, Node *t) {
    int maxflow = 0;
    while (bfs(g, s, t)) {
        int flow = getMinFlow(s, t);
        updateFlow(s, t, flow);
        maxflow += flow;
    }
    return maxflow;
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

