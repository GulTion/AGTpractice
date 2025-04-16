#include "disjoint_set.h"

DisjointSet::DisjointSet(int n) : parent(n) {
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }
}
int DisjointSet::findSet(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = findSet(parent[i]); // Path compression
}

void DisjointSet::unionSets(int i, int j) {
    int rootI = findSet(i);
    int rootJ = findSet(j);
    if (rootI != rootJ) {
        parent[rootI] = rootJ;
    }
}