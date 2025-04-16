#include<bits/stdc++.h>
using namespace std;

struct ArcNode;

struct Edge{
    int w;
    int u,v;
    bool operator<(Edge e){
        return w < e.w;
    }
};

struct Node{
    Node* next;
    int data;
    ArcNode * arc;

    Node(int n):data{n}, next{nullptr}, arc{nullptr}{};
};

struct ArcNode{
    Node * node;
    ArcNode * next;
    int w;
    ArcNode():node{nullptr}, next{nullptr}{};
};

struct Graph{

    Node *head;
    int countNodes;
    int countEdges;
    Graph():head{nullptr}{};

    void addNode(int v){
        Node * node = new Node(v);
        node->next = head;
        head = node;
        countNodes++;
    }

    void addEdge(int u, int v, int w){
        Node * src = getNode(u);
        Node * dest = getNode(v);

        ArcNode * arc = new ArcNode();
        arc->node = dest;
        arc->w = w;
        arc->next = src->arc;
        src->arc = arc;

        countEdges++;
    }

    Node *getNode(int v){
        Node * p=head;
        while(p&&p->data!=v) p=p->next;

        return p;
    }

    vector<Edge> getEdges(){
        vector<Edge> edges;

        Node * p=head;
        while(p){
            ArcNode* arc = p->arc;
            while(arc){
                edges.push_back({arc->w,p->data, arc->node->data});
                arc=arc->next;
            }
            p=p->next;
        }

        return edges;
    }
};

struct DSU{
    vector<int> p;
    DSU(int N){
        p.assign(N,0);
        for(int i=0;i<N;i++) p[i]=i;
    };

    int find(int i){
        if(p[i]==i){
            return p[i];
        }
      return p[i]=find(p[i]);
    };

    void unionSet(int a, int b){
        a = find(a);
        b = find(b);
        p[b]=a;
    };
};

int krushkal(Graph *g){
    int cost=0;
    vector<Edge> edges = g->getEdges();

    // cout<<edges.size();
    DSU *dsu = new DSU(g->countNodes);

    sort(edges.begin(), edges.end());

    for(auto [w,u,v]:edges){
        if(dsu->find(u)!=dsu->find(v)){
            cost+=w;
            cout<<u<<" "<<v<<endl;
            dsu->unionSet(u,v);
        }
    }
    return cost;
}

int main(){
    int N,E,u,v,w;

    cin>>N>>E;

    Graph * g = new Graph();

    for(int i=0;i<N;i++)g->addNode(i);

    for(int e=0;e<E;e++){
        cin>>u>>v>>w;
        g->addEdge(u,v,w);
        g->addEdge(v,u,w);
    }

    cout<<krushkal(g)<<endl;

    return 0;
}