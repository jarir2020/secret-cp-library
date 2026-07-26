#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using namespace std;

// Type aliases
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

// Constants
const int MOD = 1e9 + 7;
const int INF = 1e9;
const i64 LINF = 1e18;

// Dinic's Max Flow — O(V^2 * E)
struct Dinic {
    struct Edge { int to, rev; long long cap; };
    int n, source, sink;
    vector<vector<Edge>> graph;
    vector<int> level, iter;

    Dinic(int n, int s, int t) : n(n), source(s), sink(t), graph(n), level(n), iter(n) {}

    void add_edge(int from, int to, long long cap) {
        graph[from].push_back({to, (int)graph[to].size(), cap});
        graph[to].push_back({from, (int)graph[from].size() - 1, 0});
    }

    bool bfs() {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[source] = 0;
        q.push(source);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto& e : graph[v]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[sink] >= 0;
    }

    long long dfs(int v, long long f) {
        if (v == sink) return f;
        for (int& i = iter[v]; i < (int)graph[v].size(); i++) {
            Edge& e = graph[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
                long long d = dfs(e.to, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    graph[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    long long max_flow() {
        long long flow = 0;
        while (bfs()) {
            fill(iter.begin(), iter.end(), 0);
            long long d;
            while ((d = dfs(source, LINF)) > 0) {
                flow += d;
            }
        }
        return flow;
    }

    // Get min-cut: vertices reachable from source after max flow
    vector<int> get_min_cut() {
        vector<int> cut;
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(source);
        visited[source] = true;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            cut.push_back(v);
            for (auto& e : graph[v]) {
                if (e.cap > 0 && !visited[e.to]) {
                    visited[e.to] = true;
                    q.push(e.to);
                }
            }
        }
        return cut;
    }
};

void solve() {
    // Max flow example:
    // 0 -> 1 (10), 0 -> 2 (5), 1 -> 2 (15), 1 -> 3 (10), 2 -> 3 (10)
    int n = 4, s = 0, t = 3;
    Dinic dinic(n, s, t);

    dinic.add_edge(0, 1, 10);
    dinic.add_edge(0, 2, 5);
    dinic.add_edge(1, 2, 15);
    dinic.add_edge(1, 3, 10);
    dinic.add_edge(2, 3, 10);

    cout << "Max flow: " << dinic.max_flow() << endl; // 15

    auto cut = dinic.get_min_cut();
    cout << "Min cut vertices: ";
    for (int v : cut) cout << v << " ";
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
