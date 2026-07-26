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
const double EPS = 1e-9;

// Bellman-Ford — O(V * E)
// Finds shortest paths from source, handles negative edges, detects negative cycles
struct BellmanFord {
    struct Edge { int u, v; long long w; };
    int n;
    vector<Edge> edges;
    vector<long long> dist;
    vector<int> parent;

    BellmanFord(int n) : n(n), dist(n, LINF), parent(n, -1) {}

    void add_edge(int u, int v, long long w) {
        edges.push_back({u, v, w});
    }

    // Returns true if no negative cycle reachable from source
    bool run(int source) {
        dist[source] = 0;

        int iter = 0;
        while (iter < n - 1) {
            bool updated = false;
            for (auto& [u, v, w] : edges) {
                if (dist[u] != LINF && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    updated = true;
                }
            }
            if (!updated) break; // early termination
            iter++;
        }

        // Check for negative cycles
        int i = 0;
        while (i < (int)edges.size()) {
            auto& [u, v, w] = edges[i];
            if (dist[u] != LINF && dist[u] + w < dist[v]) {
                return false; // negative cycle exists
            }
            i++;
        }
        return true;
    }

    vector<int> get_path(int v) {
        if (dist[v] == LINF) return {};
        vector<int> path;
        for (int cur = v; cur != -1; cur = parent[cur])
            path.push_back(cur);
        reverse(path.begin(), path.end());
        return path;
    }
};

// SPFA (Shortest Path Faster Algorithm) — O(VE) average, often faster
struct SPFA {
    int n;
    vector<vector<pair<int, long long>>> adj;
    vector<long long> dist;
    vector<int> parent;
    vector<int> count;

    SPFA(int n) : n(n), adj(n), dist(n, LINF), parent(n, -1), count(n, 0) {}

    void add_edge(int u, int v, long long w) {
        adj[u].push_back({v, w});
    }

    bool run(int source) {
        dist[source] = 0;
        queue<int> q;
        vector<bool> in_queue(n, false);
        q.push(source);
        in_queue[source] = true;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            in_queue[u] = false;

            for (auto& [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    if (!in_queue[v]) {
                        q.push(v);
                        in_queue[v] = true;
                        count[v]++;
                        if (count[v] > n) return false; // negative cycle
                    }
                }
            }
        }
        return true;
    }
};

void solve() {
    int n = 5;
    BellmanFord bf(n);
    // Graph with potentially negative edges
    bf.add_edge(0, 1, 6);
    bf.add_edge(0, 3, 7);
    bf.add_edge(1, 2, 5);
    bf.add_edge(1, 3, 8);
    bf.add_edge(1, 4, -4);
    bf.add_edge(2, 1, -2);
    bf.add_edge(3, 2, -3);
    bf.add_edge(3, 4, 9);
    bf.add_edge(4, 0, 2);
    bf.add_edge(4, 2, 7);

    bool ok = bf.run(0);
    if (!ok) {
        cout << "Negative cycle detected!" << endl;
    } else {
        for (int i = 0; i < n; i++) {
            cout << "Dist to " << i << ": " << bf.dist[i] << endl;
        }
    }
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
