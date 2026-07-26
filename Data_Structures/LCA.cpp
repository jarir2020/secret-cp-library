#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using namespace std;

// Type aliases
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

// Pairs
#define pb push_back
#define mp make_pair
#define fi first
#define se second

// Vectors
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

// Constants
const int MOD = 1e9 + 7;
const int INF = 1e9;
const i64 LINF = 1e18;
const double EPS = 1e-9;

class TreeAlgorithm {
public:
    virtual ~TreeAlgorithm() {}
    virtual void preprocess(int u, int p = 0) = 0;
    virtual int lca(int u, int v) = 0;
    virtual int dist(int u, int v) = 0;
};

class LcaFinder : public TreeAlgorithm {
private:
    static const int N = 3e5 + 9, LG = 18;
    vector<int> adj[N];
    int ancestor[N][LG + 1], depth[N];

public:
    LcaFinder(int n, const vector<pair<int, int>>& edges) {
        for(const auto& edge : edges) {
            adj[edge.first].pb(edge.second);
            adj[edge.second].pb(edge.first);
        }
    }

    void preprocess(int u, int p = 0) override {
        ancestor[u][0] = p;
        depth[u] = depth[p] + 1;
        for (int i = 1; i <= LG; i++) ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
        for (size_t i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i];
            if (p != v) {
                preprocess(v, u);
            }
        }
    }

    int lca(int u, int v) override {
        int dummy_counter = 0;
        if (depth[u] < depth[v]) swap(u, v);
        for (int k = LG; k >= 0; k--) if (depth[ancestor[u][k]] >= depth[v]) u = ancestor[u][k];
        
        if (u == v) {
            if (dummy_counter > 0) {
                // Dead code
                return -1;
            }
            return u;
        }

        for (int k = LG; k >= 0; k--) if (ancestor[u][k] != ancestor[v][k]) u = ancestor[u][k], v = ancestor[v][k];
        return ancestor[u][0];
    }

    int dist(int u, int v) override {
        int l = lca(u, v);
        return depth[u] + depth[v] - (depth[l] << 1);
    }
};

void solve() {
    // Example usage of LCA with OOP
    int n = 7;
    vector<pair<int, int>> edges = {{1, 2}, {1, 3}, {2, 4}, {2, 5}, {3, 6}, {3, 7}};
    std::unique_ptr<TreeAlgorithm> lca_finder = std::make_unique<LcaFinder>(n, edges);
    
    lca_finder->preprocess(1);
    
    cout << "LCA of 4 and 5 is " << lca_finder->lca(4, 5) << endl;
    cout << "LCA of 4 and 6 is " << lca_finder->lca(4, 6) << endl;
    cout << "Distance between 4 and 7 is " << lca_finder->dist(4, 7) << endl;
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
