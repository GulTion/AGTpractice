#ifndef SET_COVER_H
#define SET_COVER_H

#include <vector>
#include <set>

// Function to compute the set cover using the greedy algorithm
std::vector<std::set<int>> greedySetCover(const std::set<int>& U, const std::vector<std::set<int>>& subsets);

#endif