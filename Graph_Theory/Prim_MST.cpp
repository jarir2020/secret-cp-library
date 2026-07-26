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

// Prim's MST — O(E log V) with priority queue
// Good for dense graphs where Kruskal's O(E log E) is slower
struct PrimMST {
    int n;
    vector<vector<pair<int,int>>> adj; // {neighbor, weight}

    PrimMST(int n) : n(n), adj(n) {}

    void add_edge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // Returns {total_cost, edges_in_MST}
    pair<long long, vector<tuple<int,int,int>>> solve(int root = 0) {
        vector<long long> key(n, LINF);
        vector<int> parent(n, -1);
        vector<bool> in_mst(n, false);
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;

        key[root] = 0;
        pq.push({0, root});
        long long total = 0;

        while (!pq.empty()) {
            auto [w, u] = pq.top(); pq.pop();
            if (in_mst[u]) continue;
            in_mst[u] = true;
            total += w;

            for (auto& [v, wt] : adj[u]) {
                if (!in_mst[v] && wt < key[v]) {
                    key[v] = wt;
                    parent[v] = u;
                    pq.push({wt, v});
                }
            }
        }

        vector<tuple<int,int,int>> edges;
        for (int i = 0; i < n; i++) {
            if (parent[i] != -1) edges.push_back({parent[i], i, (int)key[i]});
        }

        return {total, edges};
    }
};

void solve() {
    int n = 5;
    PrimMST mst(n);
    mst.add_edge(0, 1, 2);
    mst.add_edge(0, 3, 6);
    mst.add_edge(1, 2, 3);
    mst.add_edge(1, 3, 8);
    mst.add_edge(1, 4, 5);
    mst.add_edge(2, 4, 7);
    mst.add_edge(3, 4, 9);

    auto [cost, edges] = mst.solve();
    cout << "MST cost: " << cost << endl;
    cout << "Edges: ";
    for (auto& [u, v, w] : edges) cout << "(" << u << "-" << v << ":" << w << ") ";
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
