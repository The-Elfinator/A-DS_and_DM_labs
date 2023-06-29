#include <bits/stdc++.h>

static const int INF = INT_MAX;
using namespace std;

struct Edge {
    int from;
    int to;
    int capacity;
    int flow;
};

vector<vector<int>> graph;
vector<Edge> edges;
vector<bool> used;

void dfs(int v) {
    used[v] = true;
    for (int number : graph[v]) {
        Edge edge = edges[number];
        if (!used[edge.to] && edge.flow < edge.capacity) {
            dfs(edge.to);
        }
    }
}

void dump(bool flag, int n) {
    if (!flag) return;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ": ";
        for (int number : graph[i]) {
            Edge edge = edges[number];
            cout << edge.to + 1 << " c=" << edge.capacity << " f=" << edge.flow << " ; ";
        }
        cout << '\n';
    }
    cout << '\n';
}

int bfs(int vertex, int t, int n, int m) {
    queue<int> queue_v;
    vector<pair<int, int>> dist(n);
    for (int i = 0; i < n; i++) {
        dist[i].first = INF;
        dist[i].second = INF;
    }
    vector<vector<int>> path(n, vector<int>{});
    dist[vertex].first = 0;
    dist[vertex].second = INF;
    queue_v.push(vertex);
    while (!queue_v.empty()) {
        int v = queue_v.front();
        queue_v.pop();
        if (v == t) {
            break;
        }
        for (int number : graph[v]) {
            Edge& edge = edges[number];
            int to = edge.to;
            if (dist[to].first > dist[v].first + 1 && edge.flow < edge.capacity) {
                dist[to].first = dist[v].first + 1;
                path[to] = path[v];
                path[to].push_back(number);
                queue_v.push(to);
                int diff = min(dist[v].second, edge.capacity - edge.flow);
                dist[to].second = diff;
            }
        }
    }
    vector<int> minimal_path = path[t];
    if (minimal_path.empty()) {
        return 0;
    }
    int res = dist[t].second;
    for (int number : minimal_path) {
        Edge& edge = edges[number];
        edge.flow += res;
        int number_reversed = number > m ? number - m : number + m;
        Edge& reversed_edge = edges[number_reversed];
        reversed_edge.flow -= res;
    }
    return res;
}

int main() {
    bool dumpFlag = false;
    int n, m;
    cin >> n >> m;
    int s = 0; int t = n-1;
    graph.assign(n, vector<int>{});
    edges.resize(4*m);
    for (int i = 0; i < m; i++) {
        int from, to, capacity;
        cin >> from >> to >> capacity;
        from--; to--;
        Edge edge;
        edge.from = from;
        edge.to = to;
        edge.capacity = capacity;
        edge.flow = 0;
        Edge back_edge;
        back_edge.from = to;
        back_edge.to = from;
        back_edge.capacity = capacity;
        back_edge.flow = 0;
        Edge reversed_edge;
        reversed_edge.from = to;
        reversed_edge.to = from;
        reversed_edge.capacity = 0;
        reversed_edge.flow = 0;
        Edge reversed_back_edge;
        reversed_back_edge.from = from;
        reversed_back_edge.to = to;
        reversed_back_edge.capacity = 0;
        reversed_back_edge.flow = 0;
        edges[i] = edge;
        edges[m+i] = back_edge;
        edges[2*m + i] = reversed_edge;
        edges[3*m + i] = reversed_back_edge;
        graph[from].push_back(i);
        graph[from].push_back(3*m + i);
        graph[to].push_back(m+i);
        graph[to].push_back(2*m + i);
    }

    dump(dumpFlag, n);

    while(true) {
        used.assign(n, false);
        int res = bfs(s, t, n, 2*m);
        if (res == 0) {
            break;
        }
        dump(dumpFlag, n);
    }

    int F = 0;
    for (int number : graph[s]) {
        F += edges[number].flow;
    }

    used.assign(n, false);
    dfs(s);

    vector<int> ans;
    for (int i = 0; i < m; i++) {
        int v = edges[i].from;
        int to = edges[i].to;
        if (used[v] && !used[to]) {
            ans.push_back(i+1);
        }
    }
    cout << ans.size() << ' ' << F << '\n';
    for (int num : ans) {
        cout << num << ' ';
    }
    cout << '\n';
    return 0;
}
