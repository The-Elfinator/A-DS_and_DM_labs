#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> g;
vector<bool> in_match_left;
vector<bool> in_match_right;
vector<pair<int, int>> max_matching;
vector<int> from_left_to_right_in_match;
vector<bool> used;

bool find_increasing_path(int v) {
    used[v] = true;
    for (int to : g[v]) {
        if (!in_match_right[to]) {
            // found increasing path with edge v-to
            from_left_to_right_in_match[to] = v;
            in_match_right[to] = true;
            in_match_left[v] = true;
            return true;
        }
        int w = from_left_to_right_in_match[to];
        if (used[w]) {
            continue;
        }
        if (find_increasing_path(from_left_to_right_in_match[to])) {
            from_left_to_right_in_match[to] = v;
            in_match_left[v] = true;
            in_match_left[w] = false;
            return true;
        }
    }
    return false;
}

int main() {
    // input
    //--------------------------------------------------------
    int n, m;
    cin >> n >> m;
    g.assign(n, vector<int>());
    vector<int> vertex;
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        while (v != 0) {
            v--;
            vertex.push_back(v);
            cin >> v;
        }
        g[i] = vertex;
        vertex.clear();
    }
    //--------------------------------------------------------

    in_match_left.assign(n, false);
    in_match_right.assign(m, false);
    from_left_to_right_in_match.assign(m, -1);
    for (int i = 0; i < n; i++) {
        if (in_match_left[i]) {
            continue;
        }
        used.assign(n, false);
        find_increasing_path(i);

    }

    for (int i = 0; i < m; i++) {
        int v = from_left_to_right_in_match[i];
        if (v != -1) {
            max_matching.emplace_back(v+1, i+1);
        }
    }

    // output
    //---------------------------------------------------------------------------
    cout << max_matching.size() << '\n';
    for (pair<int, int> edge : max_matching) {
        cout << edge.first << ' ' << edge.second << '\n';
    }
    //---------------------------------------------------------------------------
    return 0;
}
