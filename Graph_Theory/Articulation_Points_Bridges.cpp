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

// Articulation Points and Bridges — O(V + E)
// Finds all articulation points and bridges in an undirected graph
struct ArticulationBridges {
    int n, timer;
    vector<vector<int>> adj;
    vector<int> tin, low;
    vector<bool> visited, is_articulation;
    vector<pair<int, int>> bridges;

    ArticulationBridges(int n) : n(n), timer(0), adj(n), tin(n), low(n), visited(n), is_articulation(n) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int parent = -1) {
        visited[u] = true;
        tin[u] = low[u] = timer++;
        int children = 0;

        for (int v : adj[u]) {
            if (v == parent) continue;
            if (visited[v]) {
                low[u] = min(low[u], tin[v]);
            } else {
                dfs(v, u);
                low[u] = min(low[u], low[v]);

                // Articulation point check
                if (low[v] >= tin[u] && parent != -1)
                    is_articulation[u] = true;

                // Bridge check
                if (low[v] > tin[u])
                    bridges.push_back({u, v});

                children++;
            }
        }

        if (parent == -1 && children > 1)
            is_articulation[u] = true;
    }

    void find_all() {
        int i = 0;
        while (i < n) {
            if (!visited[i]) dfs(i);
            i++;
        }
    }

    vector<int> get_articulation_points() {
        vector<int> points;
        int i = 0;
        while (i < n) {
            if (is_articulation[i]) points.push_back(i);
            i++;
        }
        return points;
    }
};

void solve() {
    int n = 6;
    ArticulationBridges ab(n);
    // Graph: 0-1, 1-2, 2-0, 2-3, 3-4, 4-5, 5-3
    ab.add_edge(0, 1);
    ab.add_edge(1, 2);
    ab.add_edge(2, 0);
    ab.add_edge(2, 3);
    ab.add_edge(3, 4);
    ab.add_edge(4, 5);
    ab.add_edge(5, 3);

    ab.find_all();

    auto ap = ab.get_articulation_points();
    cout << "Articulation points: ";
    for (int x : ap) cout << x << " ";
    cout << endl;

    cout << "Bridges: ";
    for (auto& [u, v] : ab.bridges) cout << "(" << u << ", " << v << ") ";
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
