#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<vector<int>> g;
vector<vector<int>> g_oriented;
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
            in_match_left[w] = true;
            return true;
        }
    }
    return false;
}

void find_max_matching(int size_left, int size_right) {
    in_match_left.assign(size_left, false);
    in_match_right.assign(size_right, false);
    from_left_to_right_in_match.assign(size_right, -1);
    for (int i = 0; i < size_left; i++) {
        if (in_match_left[i]) {
            continue;
        }
        used.assign(size_left, false);
        find_increasing_path(i);

    }

//    for (int i = 0; i < size_right; i++) {
//        int v = from_left_to_right_in_match[i];
//        if (v != -1) {
//            max_matching.emplace_back(v+1, i+1);
//        }
//    }

}

vector<bool> l_visited, r_visited;

void dfs(int v) {
    if (l_visited[v]) {
        return;
    }
    l_visited[v] = true;
    for (int to : g[v]) {
        if (in_match_right[to]) {
            int w = from_left_to_right_in_match[to];
            if (w != v) {
                r_visited[to] = true;
                dfs(w);
            }
        } else {
            r_visited[to] = true;
        }
    }
}

void process_request() {
    // input
    //--------------------------------------------------------
    int m, n;
    // m - юношей, n - девушек
    cin >> m >> n;
    vector<vector<int>> g_knowing;
    for (int i = 0; i < m; i++) {
        vector<int> edges;
        int x;
        cin >> x;
        while (x != 0) {
            x--;
            edges.push_back(x);
            cin >> x;
        }
        g_knowing.push_back(edges);
    }
    //--------------------------------------------------------
    // checking input
//    cout << m << " gentlemens, " << n << " ladies\n";
//    for (int i = 0; i < m; i++) {
//        cout << "Gentlemen " << i+1 << ": ";
//        for (int v : g_knowing[i]) {
//            cout << v+1 << ' ';
//        }
//        cout << '\n';
//    }
    //==============================================================
    g.assign(m, vector<int>{});
    vector<bool> knowing_ladies(n, false);
    for (int i = 0; i < m; i++) {
        for (int v : g_knowing[i]) {
            knowing_ladies[v] = true;
        }
        for (int j = 0; j < n; j++) {
            if (!knowing_ladies[j]) {
                g[i].push_back(j);
            }
        }
        knowing_ladies.assign(n, false);
    }
//    cout << "Not-g\n";
//    for (int i = 0; i < m; i++) {
//        cout << i+1 << ": ";
//        for (int v : g[i]) {
//            cout << v + 1 << ' ';
//        }
//        cout << '\n';
//    }
    find_max_matching(m, n);
    l_visited.assign(m, false);
    r_visited.assign(n, false);
    for (int i = 0; i < m; i++) {
        if (!in_match_left[i]) {
            dfs(i);
        }
    }
    // ans = l+ and r-
    vector<int> ans_gentlemens, ans_ladies;
    for (int i = 0; i < m; i++) {
        if (l_visited[i]) {
            ans_gentlemens.push_back(i);
        }
    }
    for (int i = 0; i < n; i++) {
        if (!r_visited[i]) {
            ans_ladies.push_back(i);
        }
    }
    //==============================================================
    // output
    //---------------------------------------------------------------------------
    cout << ans_gentlemens.size() + ans_ladies.size() << '\n';
    cout << ans_gentlemens.size() << ' ' << ans_ladies.size() << '\n';
    for (int v : ans_gentlemens) {
        cout << v+1 << ' ';
    }
    cout << '\n';
    for (int v : ans_ladies) {
        cout << v+1 << ' ';
    }
    cout << "\n\n";
    //---------------------------------------------------------------------------
}

int main() {
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        process_request();
    }
    return 0;
}
