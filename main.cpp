#include <iostream>
#include "task1A/Solve1A.h"

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g_left(n);
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

    vector<pair<int, int>> ans = Solve1A(n, m, g_left).findAns();

    cout << ans.size() << '\n';
    for (const pair<int, int> v_to: ans) {
        cout << v_to.first << ' ' << v_to.second << '\n';
    }

    return 0;
}
