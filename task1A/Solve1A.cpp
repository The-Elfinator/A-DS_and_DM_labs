//
// Created by artem on 29.04.2023.
//

#include "Solve1A.h"

using namespace std;

vector<bool> used;
vector<bool> in_current_matching_left;
vector<int> from_right_to_left;

Solve1A::Solve1A(int n, int m, const vector<vector<int>>& g_left) {
    this->n = n;
    this->m = m;
    this->g_left = g_left;
}

bool try_increase(int v, const vector<vector<int>> &g_left) {
    if (used[v]) {
        return false;
    }
    used[v] = true;
    for (int to: g_left[v]) {
        if (from_right_to_left[to] == -1 || try_increase(from_right_to_left[to], g_left)) {
            from_right_to_left[to] = v;
            in_current_matching_left[v] = true;
            return true;
        }
    }
    return false;
}

vector<pair<int, int>> Solve1A::findAns() const {
    in_current_matching_left.resize(this->n, false);
    from_right_to_left.resize(this->m, -1);
    for (int v = 0; v < this->n; v++) {
        used.assign(this->n, false);
        try_increase(v, this->g_left);
    }
    vector<pair<int, int>> ans;
    for (int r = 0; r < this->m; r++) {
        if (from_right_to_left[r] != -1) {
            ans.emplace_back(from_right_to_left[r] + 1, r + 1);
        }
    }
    return ans;
}
