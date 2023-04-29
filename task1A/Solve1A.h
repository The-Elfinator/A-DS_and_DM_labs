//
// Created by artem on 29.04.2023.
//
#include <utility>
#include <vector>
using namespace std;

class Solve1A {
    int n, m;
    vector<vector<int>> g_left;

public:
    Solve1A(int n, int m, const vector<vector<int>>& g_left);
    [[nodiscard]] vector<pair<int, int>> findAns() const;
};
