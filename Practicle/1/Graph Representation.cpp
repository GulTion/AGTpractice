#include <iostream>
using namespace std;

struct node;
struct arc_node;
struct graph;
struct list;

struct node {
    int data;
    node* nextNode;
    arc_node* arcHead;

    node(int n) : data(n), nextNode(nullptr), arcHead(nullptr) {}
};

struct arc_node {
    arc_node* next = nullptr;
    node* dest = nullptr;
};

struct list {
    node* head;
    node* tail;

    list() : head(nullptr), tail(nullptr) {}

    void push_back(node* newNode) {
        if (tail) {
            tail->nextNode = newNode;
            tail = newNode;
        } else {
            head = tail = newNode;
        }
    }

    void print() {
        node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->nextNode;
        }
        cout << endl;
    }
};

struct graph {
    node* head;
    int currentNodeCount;

    graph() : head(nullptr), currentNodeCount(0) {}

    ~graph() {
        node* current = head;
        while (current) {
            node* next = current->nextNode;
            arc_node* arc = current->arcHead;
            while (arc) {
                arc_node* nextArc = arc->next;
                delete arc;
                arc = nextArc;
            }
            delete current;
            current = next;
        }
    }

    void add_node(int data) {
        node* newNode = new node(data);
        newNode->nextNode = head;
        head = newNode;
        currentNodeCount++;
    }

    void add_edge(int u, int v) {
        node* src = get_node_by_index(u);
        node* dest = get_node_by_index(v);
        if (!src || !dest) {
            cout << "Invalid node index." << endl;
            return;
        }

        arc_node* arc1 = new arc_node();
        arc1->dest = dest;
        arc1->next = src->arcHead;
        src->arcHead = arc1;

        arc_node* arc2 = new arc_node();
        arc2->dest = src;
        arc2->next = dest->arcHead;
        dest->arcHead = arc2;
    }

    void delete_edge(int u, int v) {
        node* src = get_node_by_index(u);
        node* dest = get_node_by_index(v);

        if (!src || !dest) {
            cout << "Invalid node index." << endl;
            return;
        }

        // Remove the edge from src->arcHead (src -> dest)
        arc_node* prev = nullptr;
        arc_node* arc = src->arcHead;
        while (arc) {
            if (arc->dest == dest) {
                if (prev) {
                    prev->next = arc->next;
                } else {
                    src->arcHead = arc->next;
                }
                delete arc;
                break;
            }
            prev = arc;
            arc = arc->next;
        }

        // Remove the edge from dest->arcHead (dest -> src)
        prev = nullptr;
        arc = dest->arcHead;
        while (arc) {
            if (arc->dest == src) {
                if (prev) {
                    prev->next = arc->next;
                } else {
                    dest->arcHead = arc->next;
                }
                delete arc;
                break;
            }
            prev = arc;
            arc = arc->next;
        }
    }

    node* get_node_by_index(int index) {
        node* current = head;
        
        while (current && current->data != index) {
            current = current->nextNode;
        }
        return current;
    }

    void printV(int nodeIndex) {
        node* n = get_node_by_index(nodeIndex);
        if (!n) {
            cout << "Invalid node index." << endl;
            return;
        }

        cout << "Neighbors of node " << n->data << ": ";
        arc_node* arc = n->arcHead;
        while (arc) {
            cout << arc->dest->data << " ";
            arc = arc->next;
        }
        cout << endl;
    }
};

int main() {
    graph G;

    G.add_node(1);
    G.add_node(2);
    G.add_node(3);
    G.add_node(4);
    G.add_node(5);

    G.add_edge(1, 2);
    G.add_edge(1, 3);
    G.add_edge(1, 4);
    G.add_edge(1, 5);
    G.add_edge(2, 4);
    G.add_edge(3, 5);

    cout << "Neighbors of node 1 before deleting edge: ";
    G.printV(1);

    // Delete edge between node 1 and node 2
    G.delete_edge(1, 2);

    cout << "Neighbors of node 1 after deleting edge: ";
    G.printV(1);

    list L;
    node* current = G.head;
    while (current) {
        L.push_back(current);
        current = current->nextNode;
    }

    cout << "Nodes in the list: ";
    L.print();

    return 0;
}

