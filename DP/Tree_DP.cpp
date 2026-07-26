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

// Tree DP — Classic patterns

// Pattern 1: Maximum Independent Set on Tree
// Each node is either taken or not. If taken, children cannot be taken.
// dp[u][0] = max value in subtree rooted at u, u NOT taken
// dp[u][1] = max value in subtree rooted at u, u taken
struct MaxIndependentSet {
    int n;
    vector<vector<int>> adj;
    vector<vector<long long>> dp;
    vector<int> val;

    MaxIndependentSet(int n) : n(n), adj(n), dp(n, vector<long long>(2)), val(n) {}

    void set_value(int u, int v) { val[u] = v; }
    void add_edge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }

    void dfs(int u, int parent) {
        dp[u][0] = 0;       // u not taken — children can be taken or not
        dp[u][1] = val[u];  // u taken — children cannot be taken

        for (int v : adj[u]) {
            if (v == parent) continue;
            dfs(v, u);
            dp[u][0] += max(dp[v][0], dp[v][1]);
            dp[u][1] += dp[v][0];
        }
    }

    long long solve(int root = 0) {
        dfs(root, -1);
        return max(dp[root][0], dp[root][1]);
    }
};

// Pattern 2: Diameter of Tree (longest path)
struct TreeDiameter {
    int n;
    vector<vector<int>> adj;
    vector<int> dist;
    int farthest_node, max_dist;

    TreeDiameter(int n) : n(n), adj(n), dist(n) {}

    void add_edge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }

    void dfs(int u, int parent, int d) {
        dist[u] = d;
        if (d > max_dist) { max_dist = d; farthest_node = u; }
        for (int v : adj[u])
            if (v != parent) dfs(v, u, d + 1);
    }

    int get_diameter() {
        max_dist = -1;
        dfs(0, -1, 0);
        max_dist = -1;
        dfs(farthest_node, -1, 0);
        return max_dist;
    }
};

// Pattern 3: Subtree size and centroid
struct SubtreeInfo {
    int n;
    vector<vector<int>> adj;
    vector<int> subtree_size;

    SubtreeInfo(int n) : n(n), adj(n), subtree_size(n) {}

    void add_edge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }

    void dfs(int u, int parent) {
        subtree_size[u] = 1;
        for (int v : adj[u])
            if (v != parent) { dfs(v, u); subtree_size[u] += subtree_size[v]; }
    }

    // Find centroid (node where all subtrees have size <= n/2)
    int find_centroid(int u, int parent) {
        for (int v : adj[u])
            if (v != parent && subtree_size[v] > n / 2)
                return find_centroid(v, u);
        return u;
    }
};

void solve() {
    // Max Independent Set
    MaxIndependentSet mis(5);
    mis.set_value(0, 10);
    mis.set_value(1, 5);
    mis.set_value(2, 8);
    mis.set_value(3, 7);
    mis.set_value(4, 3);
    // Tree: 0-1, 0-2, 1-3, 1-4
    mis.add_edge(0, 1);
    mis.add_edge(0, 2);
    mis.add_edge(1, 3);
    mis.add_edge(1, 4);
    cout << "Max Independent Set: " << mis.solve() << endl;  // 21 (nodes 0, 3, 4 = 10+7+3, or 1,2 = 5+8 = 13... check)

    // Tree Diameter
    TreeDiameter td(4);
    td.add_edge(0, 1);
    td.add_edge(1, 2);
    td.add_edge(2, 3);
    cout << "Tree Diameter: " << td.get_diameter() << endl;  // 3

    // Subtree sizes
    SubtreeInfo si(4);
    si.add_edge(0, 1);
    si.add_edge(0, 2);
    si.add_edge(2, 3);
    si.dfs(0, -1);
    cout << "Subtree sizes: ";
    for (int i = 0; i < 4; i++) cout << si.subtree_size[i] << " ";
    cout << endl;  // 4 1 2 1
    cout << "Centroid: " << si.find_centroid(0, -1) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
