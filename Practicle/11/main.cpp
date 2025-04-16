#include <iostream>
#include <vector>
#include <limits>
#include <numeric>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max() / 2;
const int NEG_INF = numeric_limits<int>::min() / 2;

int hungarian_max_weight_minimal(const vector<vector<int>>& C, vector<int>& assignment) {
    if (C.empty() || C[0].size() != C.size()) return NEG_INF;
    int n = C.size();
    if (n == 0) return 0;

    vector<int> u(n + 1, 0), v(n + 1, 0), p(n + 1, 0), way(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        auto max_it = max_element(C[i - 1].begin(), C[i - 1].end());
        u[i] = (max_it != C[i - 1].end()) ? *max_it : 0; 
    }


    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int j0 = 0;
        vector<int> min_s(n + 1, INF);
        vector<bool> vis(n + 1, false);

        do {
            vis[j0] = true;
            int i0 = p[j0], delta = INF, j1 = -1;

            for (int j = 1; j <= n; ++j) {
                if (!vis[j]) {
                    int cur_s = u[i0] + v[j] - C[i0 - 1][j - 1];
                    if (cur_s < min_s[j]) {
                        min_s[j] = cur_s;
                        way[j] = j0;
                    }
                    if (min_s[j] < delta) {
                        delta = min_s[j];
                        j1 = j;
                    }
                }
            }

            if (delta == INF) return NEG_INF; // Error condition

            for (int j = 0; j <= n; ++j) {
                if (vis[j]) {
                    u[p[j]] -= delta;
                    v[j] += delta;
                } else {
                    min_s[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);

        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    assignment.assign(n, -1);
    int totalWeight = 0;
    for (int j = 1; j <= n; ++j) {
        if (p[j] > 0) {
            assignment[p[j] - 1] = j - 1;
            totalWeight += C[p[j] - 1][j - 1];
        }
    }
    return totalWeight;
}

// Minimal main for testing
#include <iostream>
int main() {
     vector<vector<int>> weights = {
        {8, 2, 6, 7},
        {7, 9, 5, 4},
        {6, 3, 8, 5},
        {4, 7, 4, 6}
    };
    vector<int> assignment;
    int maxW = hungarian_max_weight_minimal(weights, assignment);
    cout << "Max Weight: " << maxW << endl;
    if (maxW > NEG_INF) {
        for(int i=0; i<assignment.size(); ++i) cout << i << "->" << assignment[i] << " ";
        cout << endl;
    }
    return 0;
}