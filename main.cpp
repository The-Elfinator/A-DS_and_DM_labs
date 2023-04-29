#include <bits/stdc++.h>
#include <iostream>

using namespace std;

vector<vector<int>> g_left;
vector<bool> in_current_matching_left;
vector<int> from_right_to_left;
vector<bool> used;

bool try_increase(int v) {
    if (used[v]) {
        return false;
    }
    used[v] = true;
    for (int to: g_left[v]) {
        if (from_right_to_left[to] == -1 || try_increase(from_right_to_left[to])) {
            from_right_to_left[to] = v;
            in_current_matching_left[v] = true;
            return true;
        }
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    g_left.resize(n);
    in_current_matching_left.resize(n, false);
    from_right_to_left.resize(m, -1);
    for (int i = 0; i < n; i++) {
        vector<int> vect;
        int v;
        cin >> v;
        while (v != 0) {
            v--;
            vect.push_back(v);
            cin >> v;
        }
        g_left[i] = vect;
    }

    for (int v = 0; v < n; v++) {
        used.assign(n, false);
        try_increase(v);
    }

    vector<pair<int, int>> ans;
    for (int r = 0; r < m; r++) {
        if (from_right_to_left[r] != -1) {
            ans.emplace_back(from_right_to_left[r] + 1, r + 1);
        }
    }

    cout << ans.size() << '\n';
    for (const pair<int, int> v_to: ans) {
        cout << v_to.first << ' ' << v_to.second << '\n';
    }

    return 0;
}
