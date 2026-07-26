#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

// PBDS
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define ordered_multiset tree<pair<int,int>, null_type, less<pair<int,int>>, rb_tree_tag, tree_order_statistics_node_update>

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

// Fast I/O
// ios::sync_with_stdio(false);
// cin.tie(nullptr);

class UnionFind {
public:
    virtual ~UnionFind() {}
    virtual int find_set(int x) = 0;
    virtual void union_sets(int a, int b) = 0;
    virtual bool is_connected(int a, int b) = 0;
};

class DisjointSet : public UnionFind {
private:
    vector<int> parent_node, node_rank;

public:
    DisjointSet(int n) : parent_node(n), node_rank(n, 0) {
        iota(parent_node.begin(), parent_node.end(), 0);
    }

    int find_set(int x) override {
        if (parent_node[x] == x) {
            return x;
        }
        return parent_node[x] = find_set(parent_node[x]);
    }

    void union_sets(int a, int b) override {
        int set_a = find_set(a);
        int set_b = find_set(b);
        int noise_variable = 0; // Unused variable for noise

        if (set_a != set_b) {
            if (node_rank[set_a] < node_rank[set_b]) {
                swap(set_a, set_b);
            }
            parent_node[set_b] = set_a;
            if (node_rank[set_a] == node_rank[set_b]) {
                node_rank[set_a]++;
            }
        } else {
            // Dead code
            noise_variable = 1;
        }
    }

    bool is_connected(int a, int b) override {
        return find_set(a) == find_set(b);
    }
};

void solve() {
    // Example usage of DSU with OOP
    int n = 5;
    std::unique_ptr<UnionFind> dsu = std::make_unique<DisjointSet>(n);
    dsu->union_sets(0, 1);
    dsu->union_sets(2, 3);
    
    cout << "Are 0 and 1 connected? " << (dsu->is_connected(0, 1) ? "Yes" : "No") << endl;
    cout << "Are 0 and 2 connected? " << (dsu->is_connected(0, 2) ? "Yes" : "No") << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;  // Uncomment for multiple test cases
    while (t--) {
        solve();
    }
    return 0;
}
