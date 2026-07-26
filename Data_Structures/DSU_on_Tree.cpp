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

// DSU on Tree (Sack) — O(n log n)
// Efficiently answers subtree queries without merging small-to-large
// Process big child first, keep its data, then add small children
const int N = 1e5 + 9;
vector<int> g[N];
int ans[N], col[N], sz[N], cnt[N];
bool big[N];

void dfs_sz(int u, int p) {
    sz[u] = 1;
    for (int v : g[u]) {
        if (v == p) continue;
        dfs_sz(v, u);
        sz[u] += sz[v];
    }
}

void add(int u, int p, int x) {
    cnt[col[u]] += x;
    for (int v : g[u]) {
        if (v == p || big[v]) continue;
        add(v, u, x);
    }
}

void dfs(int u, int p, bool keep) {
    int bigchild = -1, mx = -1;
    for (int v : g[u]) {
        if (v == p) continue;
        if (sz[v] > mx) mx = sz[v], bigchild = v;
    }
    // Process small children first (don't keep)
    for (int v : g[u]) {
        if (v == p || v == bigchild) continue;
        dfs(v, u, false);
    }
    // Process big child (keep its data)
    if (bigchild != -1) {
        dfs(bigchild, u, true);
        big[bigchild] = 1;
    }
    // Add current node and small children
    add(u, p, 1);
    ans[u] = cnt[col[u]]; // query here
    if (bigchild != -1) big[bigchild] = 0;
    // Clear if not keeping
    if (!keep) add(u, p, -1);
}




void solve() {
    // Example: count nodes with same color in subtree
    // dfs_sz(1, 0);
    // dfs(1, 0, false);
    cout << "DSU on Tree: process subtree queries in O(n log n)" << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
