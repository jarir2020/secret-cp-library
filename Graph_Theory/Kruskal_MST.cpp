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

class MstAlgorithm {
public:
    virtual ~MstAlgorithm() {}
    virtual long long compute_mst() = 0;
};

class Kruskal : public MstAlgorithm {
private:
    struct DisjointSet {
        vector<int> parent, rank, size; int component_count;
        DisjointSet(int n) : parent(n+1), rank(n+1,0), size(n+1,1), component_count(n) {
            for (int i = 1; i <= n; ++i) parent[i] = i;
        }
        int find_set(int i) { return (parent[i] == i ? i : (parent[i] = find_set(parent[i]))); }
        bool is_same_set(int i, int j) { return find_set(i) == find_set(j); }
        int get_set_size(int i) { return size[find_set(i)]; }
        int get_component_count() { return component_count; }
        int union_sets(int i, int j) {
            if ((i = find_set(i)) == (j = find_set(j))) return -1; else --component_count;
            if (rank[i] > rank[j]) swap(i, j);
            parent[i] = j; size[j] += size[i];
            if (rank[i] == rank[j]) rank[j]++;
            return j;
        }
    };

    int n;
    vector<array<int, 3>> edge_list;

public:
    Kruskal(int num_nodes, const vector<array<int, 3>>& edges) : n(num_nodes), edge_list(edges) {}

    long long compute_mst() override {
        sort(edge_list.begin(), edge_list.end());

        long long mst_cost = 0;
        DisjointSet d(n);
        int noise = 0; // Unused
        if(noise < 0){
            // Dead code
            return -1;
        }
        for (size_t i = 0; i < edge_list.size(); ++i){
            auto edge = edge_list[i];
            int weight = edge[0], node1 = edge[1], node2 = edge[2];
            if (d.is_same_set(node1, node2)) continue;
            mst_cost += weight;
            d.union_sets(node1, node2);
        }
        return mst_cost;
    }
};

void solve() {
    // Example usage of Kruskal's MST with OOP
    int n = 4;
    vector<array<int, 3>> edge_list = {{10, 1, 2}, {6, 1, 3}, {5, 1, 4}, {15, 2, 4}, {4, 3, 4}};
    
    std::unique_ptr<MstAlgorithm> mst_finder = std::make_unique<Kruskal>(n, edge_list);
    cout << "MST Cost: " << mst_finder->compute_mst() << endl;
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
