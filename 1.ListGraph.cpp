#include<bits/stdc++.h>
using namespace std;
struct Node;
struct ArcNode{
    Node * node;
    ArcNode * nextArc;

    ArcNode():node(nullptr), nextArc(nullptr){};
};

struct Node{
        int data;
        bool visited;
        Node * nextNode;
        ArcNode * arc;
        Node(int d):data(d), nextNode(nullptr), arc(nullptr), visited(false){};
};



struct Graph{
    Node *head;
    Graph():head(nullptr){};

    void addNode(int v){
        Node * node = new Node(v);
        node->nextNode=head;
        head=node;
    }

    void addEdge(int u,int v){
        Node * src = getNode(u);
        Node * dest = getNode(v);

        ArcNode * arc = new ArcNode();

        arc->nextArc = src->arc;
        arc->node=dest;
        src->arc=arc;

    }

    Node * getNode(int n){
        Node * p=head;
        while(p && p->data!=n) p=p->nextNode;
        return p;
    }

    void printV(int v){
        Node *p=head;
        while(p->data!=v) p=p->nextNode;
        ArcNode * a=p->arc;
        while(a){
            cout<<a->node->data<<" ";
            a = a->nextArc;
        }
    }
};

void dfs(Node * p){
    if(!p||p->visited) return;
    cout<<p->data<<" ";
    p->visited=true;
    ArcNode * a = p->arc;
    while(a) dfs(a->node),a=a->nextArc;
}

int main(){
    int N,E, u,v;
    cin>>N>>E;
    Graph *graph = new Graph();
    for(int v=0;v<N;v++) graph->addNode(v);

    for(int e=0;e<E;e++){
        cin>>u>>v;
        graph->addEdge(u,v);
    }

    dfs(graph->head);



    return 0;
}