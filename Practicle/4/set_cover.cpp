#include "set_cover.h"
#include <algorithm>

std::vector<std::set<int>> greedySetCover(const std::set<int>& U, const std::vector<std::set<int>>& subsets) {
    std::vector<std::set<int>> cover;
    std::set<int> uncovered = U;

    while (!uncovered.empty()) {
        std::set<int> bestSubset;
        int maxCovered = 0;

        for (const auto& subset : subsets) {
            std::set<int> intersection;
            std::set_intersection(subset.begin(), subset.end(),
                                  uncovered.begin(), uncovered.end(),
                                  std::inserter(intersection, intersection.begin()));
            
            if (intersection.size() > maxCovered) {
                maxCovered = intersection.size();
                bestSubset = subset;
            }
        }

        cover.push_back(bestSubset);
        for (int element : bestSubset) {
            uncovered.erase(element);
        }
    }

    return cover;
}