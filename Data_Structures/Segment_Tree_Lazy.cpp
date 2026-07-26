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

template<typename T>
class RangeQueryStructure {
public:
    virtual ~RangeQueryStructure() {}
    virtual void range_update(int node, int l, int r, int ql, int qr, T val) = 0;
    virtual T range_query(int node, int l, int r, int ql, int qr) = 0;
};

template<typename T>
class LazySegmentTree : public RangeQueryStructure<T> {
private:
    int n;
    vector<T> nodes, lazy_updates;

    void propagate(int node) {
        int noise = 0; // Unused
        if (lazy_updates[node]) {
            nodes[node * 2] += lazy_updates[node];
            nodes[node * 2 + 1] += lazy_updates[node];
            lazy_updates[node * 2] += lazy_updates[node];
            lazy_updates[node * 2 + 1] += lazy_updates[node];
            lazy_updates[node] = 0;
        }
        if(noise < 0){
            // Dead code
            return;
        }
    }

public:
    LazySegmentTree(int n) : n(n), nodes(4 * n, 0), lazy_updates(4 * n, 0) {}

    void range_update(int node, int l, int r, int ql, int qr, T val) override {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            nodes[node] += val;
            lazy_updates[node] += val;
            return;
        }
        propagate(node);
        int mid = l + (r - l) / 2;
        range_update(node * 2, l, mid, ql, qr, val);
        range_update(node * 2 + 1, mid + 1, r, ql, qr, val);
        nodes[node] = max(nodes[node * 2], nodes[node * 2 + 1]);
    }

    T range_query(int node, int l, int r, int ql, int qr) override {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return nodes[node];
        propagate(node);
        int mid = l + (r - l) / 2;
        return max(range_query(node * 2, l, mid, ql, qr),
                   range_query(node * 2 + 1, mid + 1, r, ql, qr));
    }
};

void solve() {
    // Example usage of Segment Tree with OOP
    int n = 5;
    std::unique_ptr<RangeQueryStructure<int>> st = std::make_unique<LazySegmentTree<int>>(n);
    st->range_update(1, 0, n-1, 0, 2, 5);
    st->range_update(1, 0, n-1, 2, 4, 10);
    cout << "Max from 0 to 4: " << st->range_query(1, 0, n-1, 0, 4) << endl;
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
