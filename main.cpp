#include <bits/stdc++.h>

static const int INF = INT_MAX;
using namespace std;

int main() {
    ifstream fin("assignment.in");
    int n;
    fin >> n;
    int C[n+1][n+1];
    for (int i = 0; i <= n; i++) {
        C[i][0] = 0;
    }
    for (int j = 0; j <= n; j++) {
        C[0][j] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x;
            fin >> x;
            C[i][j] = x;
        }
    }
    fin.close();
    //-------------------------------------------------------------------------------

    vector<int> pot_row(n+1);
    vector<int> pot_col(n+1);
    vector<int> matching(n+1);
    vector<int> path(n+1);
    for (int i=1; i<=n; ++i) {
        matching[0] = i;
        int index0 = 0;
        vector<int> min_col(n+1, INF);
        vector<char> used (n+1, false);
        do {
            used[index0] = true;
            int current_index = matching[index0], diff = INF, index1;
            for (int j=1; j<=n; ++j)
                if (!used[j]) {
                    int cur = C[current_index][j]- pot_row[current_index]- pot_col[j];
                    if (cur < min_col[j])
                        min_col[j] = cur, path[j] = index0;
                    if (min_col[j] < diff)
                        diff = min_col[j], index1 = j;
                }
            for (int j=0; j<=n; ++j)
                if (used[j])
                    pot_row[matching[j]] += diff, pot_col[j] -= diff;
                else
                    min_col[j] -= diff;
            index0 = index1;
        } while (matching[index0] != 0);
        do {
            int index1 = path[index0];
            matching[index0] = matching[index1];
            index0 = index1;
        } while (index0 != 0);
    }
    vector<int> ans(n+1);
    for (int j = 1; j<=n; j++) {
        ans[matching[j]] = j;
    }
    int cost = 0;
    for (int i = 1; i <= n; i++) {
        cost += C[i][ans[i]];
    }

    //-------------------------------------------------------------------------------
    ofstream fout("assignment.out");
    fout << cost << endl;
    for (int i = 1; i <= n; i++) {
        fout << i << ' ' << ans[i] << endl;
    }
    fout.close();
    return 0;
}
