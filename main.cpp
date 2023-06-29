#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<bool> in_match_left;
vector<bool> in_match_right;
vector<int> from_right_to_left_in_match;
vector<bool> used;
vector<int> ans;

bool find_increasing_path(int v) {
    used[v] = true;
    for (int to : g[v]) {
        if (!in_match_right[to]) {
            // found increasing path with edge v-to
            from_right_to_left_in_match[to] = v;
            in_match_right[to] = true;
            in_match_left[v] = true;
            return true;
        }
        int w = from_right_to_left_in_match[to];
        if (used[w]) {
            continue;
        }
        if (find_increasing_path(from_right_to_left_in_match[to])) {
            from_right_to_left_in_match[to] = v;
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
    from_right_to_left_in_match.assign(size_right, -1);
    for (int i = 0; i < size_left; i++) {
        if (in_match_left[i]) {
            continue;
        }
        used.assign(size_left, false);
        find_increasing_path(i);

    }

//    for (int i = 0; i < size_right; i++) {
//        int v = from_right_to_left_in_match[i];
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
            int w = from_right_to_left_in_match[to];
            if (w != v) {
                r_visited[to] = true;
                dfs(w);
            }
        } else {
            r_visited[to] = true;
        }
    }
}

void process_request(int n) {

    find_max_matching(n, n);
    l_visited.assign(n, false);
    r_visited.assign(n, false);
    for (int i = 0; i < n; i++) {
        if (!in_match_left[i]) {
            dfs(i);
        }
    }
    // MVC = l- and r+
    // В ответ те вершины, которые не в l- и не в r+ то есть
    for (int i = 0; i < n; i++) {
        if (l_visited[i] && !(r_visited[i])) {
            ans.push_back(i);
        }
    }
}

int main() {
    ifstream fin("hobbits.in");
    int n;
    fin >> n;
    vector<vector<int>> matrix(n, vector<int>{});
    for (int i = 0; i < n; i++) {
        int a;
        for (int j = 0; j < n; j++) {
            fin >> a;
            matrix[i].push_back(a);
        }
    }
    fin.close();

    // транзитивное замыкание графа
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][j] = matrix[i][k] * matrix[k][j];
                }
            }
        }
    }

    g.assign(n, vector<int>{});
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1) {
                g[i].push_back(j);
            }
        }
    }

//    for (int i = 0; i < n; i++) {
//        cout << i + 1 << ": ";
//        for (int v: g[i]) {
//            cout << v + 1 << ' ';
//        }
//        cout << '\n';
//    }

    process_request(n);

    ofstream fout("hobbits.out");
    fout << ans.size() << '\n';
    for (int v : ans) {
        fout << v+1 << ' ';
    }
    fout << '\n';
    fout.close();
    return 0;
}
