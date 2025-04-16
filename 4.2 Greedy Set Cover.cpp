#include <bits/stdc++.h>
using namespace std;

// Greedy Set Cover Algorithm (Concise and Correct)
vector<set<int>> greedySetCoverConcise(set<int> X, vector<set<int>> F) {
    set<int> U = X;
    vector<set<int>> C;

    while (!U.empty()) {
        auto bestIt = F.end(); // use iterator
        int maxCover = 0;

        for (auto it = F.begin(); it != F.end(); ++it) {
            set<int> intersection;
            set_intersection(
                U.begin(), U.end(),
                it->begin(), it->end(),
                inserter(intersection, intersection.begin())
            );

            if (intersection.size() > maxCover) {
                maxCover = intersection.size();
                bestIt = it;
            }
        }

        if (bestIt == F.end()) break; // no more useful sets

        // Add to cover
        C.push_back(*bestIt);

        // Remove covered elements from U
        for (int i : *bestIt) {
            U.erase(i);
        }
    }

    return C;
}

void print_result(const vector<set<int>>& C) {
    cout << "Cover using " << C.size() << " sets:\n";
    for (const auto& s : C) {
        for (int i : s) cout << i << " ";
        cout << "\n";
    }
}

int main() {
    set<int> universe = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<set<int>> family = {
        {1, 2, 3, 8}, {1, 2, 3, 4, 5}, {4, 5, 7},
        {5, 6, 7, 9, 10}, {6, 7, 8, 9, 10}
    };

    vector<set<int>> result = greedySetCoverConcise(universe, family);
    print_result(result);

    return 0;
}

