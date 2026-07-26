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

// Heavy Light Decomposition — O(log^2 n) per path query
// Decomposes tree into chains so path queries become range queries on segments
const int N = 1e5 + 9, LG = 17;

struct HLD {
    int n, root;
    vector<int> adj[N];
    int par[N][LG+1], dep[N], sz[N], big[N];
    int head[N], pos[N], timer;

    HLD(int n, int root = 1) : n(n), root(root), timer(0) {
        memset(big, 0, sizeof big);
        for (int i = 0; i <= n; i++) head[i] = i;
    }

    void add_edge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }

    void dfs(int u, int p) {
        par[u][0] = p; dep[u] = dep[p] + 1; sz[u] = 1;
        for (int i = 1; i <= LG; i++) par[u][i] = par[par[u][i-1]][i-1];
        for (int &v : adj[u]) {
            if (v == p) continue;
            dfs(v, u);
            sz[u] += sz[v];
            if (sz[v] > sz[adj[u][0]] && v != adj[u][0]) swap(v, adj[u][0]);
        }
    }

    void decompose(int u, int p, int h) {
        head[u] = h; pos[u] = timer++;
        if (!adj[u].empty() && adj[u][0] != p) decompose(adj[u][0], u, h);
        for (int v : adj[u]) {
            if (v == p || v == adj[u][0]) continue;
            decompose(v, u, v);
        }
    }

    int lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        for (int k = LG; k >= 0; k--)
            if (dep[par[u][k]] >= dep[v]) u = par[u][k];
        if (u == v) return u;
        for (int k = LG; k >= 0; k--)
            if (par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
        return par[u][0];
    }

    // Process path from u to v — callback({l, r}) for each chain segment
    template<class F>
    void path_query(int u, int v, F&& process) {
        while (head[u] != head[v]) {
            if (dep[head[u]] < dep[head[v]]) swap(u, v);
            process(pos[head[u]], pos[u]);
            u = par[head[u]][0];
        }
        if (dep[u] > dep[v]) swap(u, v);
        process(pos[u], pos[v]);
    }

    void init() {
        dfs(root, 0);
        decompose(root, 0, root);
    }
};

void solve() {
    HLD hld(5);
    hld.add_edge(1, 2); hld.add_edge(1, 3); hld.add_edge(2, 4); hld.add_edge(2, 5);
    hld.init();
    cout << "LCA(4,5) = " << hld.lca(4, 5) << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
