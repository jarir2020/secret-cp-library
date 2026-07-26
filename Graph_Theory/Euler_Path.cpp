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

// Euler Path / Circuit — Hierholzer's Algorithm — O(E)
// For undirected graphs: Euler circuit exists iff all vertices have even degree
//                         Euler path exists iff exactly 0 or 2 vertices have odd degree
struct EulerPath {
    int n;
    vector<vector<pair<int, int>>> adj; // {neighbor, edge_id}
    vector<int> degree;
    vector<bool> used_edge;
    vector<int> path;

    EulerPath(int n) : n(n), adj(n), degree(n, 0) {}

    void add_edge(int u, int v, int id) {
        adj[u].push_back({v, id});
        adj[v].push_back({u, id});
        degree[u]++;
        degree[v]++;
    }

    void dfs(int u) {
        while (!adj[u].empty()) {
            auto [v, id] = adj[u].back();
            adj[u].pop_back();
            if (used_edge[id]) continue;
            used_edge[id] = true;
            dfs(v);
        }
        path.push_back(u);
    }

    // Returns the Euler path/circuit (in reverse order, reverse before using)
    // Returns empty if no Euler path exists
    vector<int> find_euler_path() {
        // Count odd-degree vertices
        vector<int> odd_vertices;
        for (int i = 0; i < n; i++) {
            if (degree[i] % 2 == 1) odd_vertices.push_back(i);
        }

        if (odd_vertices.size() != 0 && odd_vertices.size() != 2) {
            return {}; // No Euler path
        }

        used_edge.assign(2 * n, false); // max edges
        int start = (odd_vertices.size() == 2) ? odd_vertices[0] : 0;

        dfs(start);
        reverse(path.begin(), path.end());
        return path;
    }
};

// Directed Euler Path / Circuit
struct DirectedEulerPath {
    int n;
    vector<vector<int>> adj;
    vector<int> in_degree, out_degree;
    vector<int> path;

    DirectedEulerPath(int n) : n(n), adj(n), in_degree(n, 0), out_degree(n, 0) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        out_degree[u]++;
        in_degree[v]++;
    }

    void dfs(int u) {
        while (!adj[u].empty()) {
            int v = adj[u].back();
            adj[u].pop_back();
            dfs(v);
        }
        path.push_back(u);
    }

    vector<int> find_euler_path() {
        // Check: at most one vertex with out - in = 1 (start)
        //        at most one vertex with in - out = 1 (end)
        //        all others have in == out
        int start = -1, end = -1;
        for (int i = 0; i < n; i++) {
            int diff = out_degree[i] - in_degree[i];
            if (diff == 1) {
                if (start != -1) return {};
                start = i;
            } else if (diff == -1) {
                if (end != -1) return {};
                end = i;
            } else if (diff != 0) {
                return {};
            }
        }

        if (start == -1) {
            // All degrees equal — circuit, start anywhere with edges
            for (int i = 0; i < n; i++) {
                if (!adj[i].empty()) { start = i; break; }
            }
        }
        if (start == -1) return {}; // no edges

        dfs(start);
        reverse(path.begin(), path.end());
        return path;
    }
};

void solve() {
    // Undirected Euler Path example
    int n = 5;
    EulerPath ep(n);
    ep.add_edge(0, 1, 0);
    ep.add_edge(1, 2, 1);
    ep.add_edge(2, 0, 2);
    ep.add_edge(2, 3, 3);
    ep.add_edge(3, 4, 4);

    auto path = ep.find_euler_path();
    if (path.empty()) {
        cout << "No Euler path exists" << endl;
    } else {
        cout << "Euler path: ";
        for (int x : path) cout << x << " ";
        cout << endl;
    }

    // Directed Euler Circuit example
    DirectedEulerPath dep(4);
    dep.add_edge(0, 1);
    dep.add_edge(1, 2);
    dep.add_edge(2, 0);
    dep.add_edge(0, 3);
    dep.add_edge(3, 0);

    auto dpath = dep.find_euler_path();
    if (!dpath.empty()) {
        cout << "Directed Euler path: ";
        for (int x : dpath) cout << x << " ";
        cout << endl;
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
