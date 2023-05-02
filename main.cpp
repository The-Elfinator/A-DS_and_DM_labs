#include "task1A/Solve1A.h"
#include <iostream>
#include <vector>

using namespace std;


void completeRequest() {
    int n, m;
    cin >> m >> n;
    bool swapped = false;
    if (m >= n) {
        swapped = true;
        swap(n, m);
    }
    // n юношей >= m девушек
    vector<vector<int>> g(n);
    for (int i = 0; i < n; i++) {
        vector<int> edges;
        int x;
        cin >> x;
        while (x != 0) {
            x--;
            edges.push_back(x);
            cin >> x;
        }
        g[i] = edges;
    }

    vector<vector<int>> not_g(n);
    for (int i = 0; i < n; i++) {
        vector<bool> used(m, false);
        for (int v: g[i]) {
            used[v] = true;
        }
        for (int j = 0; j < m; j++) {
            if (!used[j]) {
                not_g[i].push_back(j);
            }
        }
    }

    // TODO: find max matching in not_g and print not-answer of max matching
    vector<pair<int, int>> find_max_matching = (new Solve1A(n, m, not_g))->findAns();
    vector<bool> ans_gentlemens(n, true);
    int count_gentlemens = n;
    vector<bool> ans_ladies(m, false);
    int count_ladies = 0;
    for (pair<int, int> p: find_max_matching) {
        int left = p.first - 1;
        ans_gentlemens[left] = false;
        count_gentlemens--;
    }
    for (int i = 0; i < n; i++) {
        for (int right: g[i]) {
            if (!ans_ladies[right]) {
                ans_ladies[right] = true;
                count_ladies++;
            }
        }
    }
    if (!swapped) {
        swap(count_ladies, count_gentlemens);
        swap(ans_ladies, ans_gentlemens);
    }

    cout << count_ladies + count_gentlemens << '\n';
    cout << count_gentlemens << ' ' << count_ladies << '\n';
    for (int i = 0; i < n; i++) {
        if (ans_gentlemens[i]) {
            cout << i + 1 << ' ';
        }
    }
    cout << '\n';
    for (int i = 0; i < m; i++) {
        if (ans_ladies[i]) {
            cout << i + 1 << ' ';
        }
    }
    cout << "\n";
}

int main() {
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        completeRequest();
        cout << '\n';
    }

    return 0;
}
