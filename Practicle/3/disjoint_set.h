#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <vector>

class DisjointSet {
public:
    DisjointSet(int n);
    int findSet(int i);
    void unionSets(int i, int j);
private:
    std::vector<int> parent;
};

#endif