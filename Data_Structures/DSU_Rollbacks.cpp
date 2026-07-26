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

// DSU with Rollbacks — O(log n) per merge, O(log n) per undo
// Also checks bipartiteness during merges
// Useful for offline divide-and-conquer on edges
struct DSU_Rollback {
    vector<int> par, sz, w;
    vector<array<int, 3>> op; // {u, old_w, old_flag}
    bool flag; // bipartite flag

    DSU_Rollback() {}
    DSU_Rollback(int n) : par(n+1), sz(n+1, 1), w(n+1, 0), flag(true) {
        for (int i = 1; i <= n; i++) par[i] = i;
    }

    pair<int, int> find(int u) {
        int ans = 0;
        while (par[u] != u) {
            ans ^= w[u];
            u = par[u];
        }
        return {u, ans};
    }

    bool merge(int u, int v) {
        auto pu = find(u), pv = find(v);
        u = pu.first; v = pv.first;
        int last = flag;
        int z = pu.second ^ pv.second ^ 1;
        if (u == v) {
            if (z) flag = false;
            op.push_back({-1, -1, last});
            return false;
        }
        if (sz[u] > sz[v]) swap(u, v);
        op.push_back({u, w[u], last});
        par[u] = v; w[u] = z;
        sz[v] += sz[u];
        return true;
    }

    void undo() {
        assert(!op.empty());
        auto x = op.back(); op.pop_back();
        flag = x[2];
        int u = x[0];
        if (u != -1) {
            sz[par[u]] -= sz[u];
            par[u] = u; w[u] = x[1];
        }
    }

    bool is_bipartite() { return flag; }
};




void solve() {
    DSU_Rollback dsu(5);
    dsu.merge(1, 2);
    dsu.merge(2, 3);
    cout << "Bipartite after merges: " << dsu.is_bipartite() << endl;
    dsu.undo();
    dsu.undo();
    cout << "After 2 undos, still bipartite: " << dsu.is_bipartite() << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
