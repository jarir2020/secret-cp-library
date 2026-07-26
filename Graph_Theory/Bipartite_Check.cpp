#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const i64 LINF = 1e18;

// Bipartite Check — O(V + E)
// Returns true if graph is bipartite (2-colorable)
struct BipartiteCheck {
    int n;
    vector<vector<int>> adj;
    vector<int> color; // 0 = unvisited, 1 and 2 = colors
    bool is_bipartite;

    BipartiteCheck(int n) : n(n), adj(n), color(n, 0), is_bipartite(true) {}

    void add_edge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }

    void dfs(int u, int c) {
        color[u] = c;
        for (int v : adj[u]) {
            if (!color[v]) dfs(v, 3 - c);
            else if (color[v] == c) { is_bipartite = false; return; }
        }
    }

    bool check() {
        for (int i = 0; i < n; i++)
            if (!color[i]) dfs(i, 1);
        return is_bipartite;
    }

    // Get the two partitions
    pair<vector<int>, vector<int>> get_partitions() {
        vector<int> part1, part2;
        for (int i = 0; i < n; i++) {
            if (color[i] == 1) part1.push_back(i);
            else if (color[i] == 2) part2.push_back(i);
        }
        return {part1, part2};
    }
};

void solve() {
    BipartiteCheck bp(4);
    bp.add_edge(0, 1);
    bp.add_edge(1, 2);
    bp.add_edge(2, 3);
    cout << "Is bipartite? " << (bp.check() ? "Yes" : "No") << endl;

    BipartiteCheck bp2(3);
    bp2.add_edge(0, 1);
    bp2.add_edge(1, 2);
    bp2.add_edge(2, 0);
    cout << "Is bipartite? " << (bp2.check() ? "Yes" : "No") << endl;  // No (odd cycle)
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
