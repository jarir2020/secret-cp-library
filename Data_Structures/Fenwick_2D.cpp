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

// 2D Fenwick Tree — O(log n * log m) per operation
// Three variants: point update/range query, range update/point query, full range

// Variant 1: Point Update + Range Query
template <typename T>
struct Fenwick2D_PointUpdate {
    int n, m;
    vector<vector<T>> tree;
    Fenwick2D_PointUpdate(int n, int m) : n(n), m(m), tree(n+1, vector<T>(m+1, 0)) {}

    void update(int i, int j, T v) {
        for (int x = i; x <= n; x += x & -x)
            for (int y = j; y <= m; y += y & -y)
                tree[x][y] += v;
    }

    T query(int i, int j) {
        if (i <= 0 || j <= 0) return 0;
        T res = 0;
        for (int x = i; x > 0; x -= x & -x)
            for (int y = j; y > 0; y -= y & -y)
                res += tree[x][y];
        return res;
    }

    T query(int i, int j, int k, int l) {
        return query(k, l) - query(i-1, l) - query(k, j-1) + query(i-1, j-1);
    }
};

// Variant 2: Range Update + Point Query
template <typename T>
struct Fenwick2D_RangeUpdate {
    int n, m;
    vector<vector<T>> tree;
    Fenwick2D_RangeUpdate(int n, int m) : n(n), m(m), tree(n+1, vector<T>(m+1, 0)) {}

    void update(int i, int j, T v) {
        for (int x = i; x <= n; x += x & -x)
            for (int y = j; y <= m; y += y & -y)
                tree[x][y] += v;
    }

    void update(int i, int j, int k, int l, T v) {
        update(i, j, v); update(k+1, j, -v);
        update(k+1, l+1, v); update(i, l+1, -v);
    }

    T query(int i, int j) {
        T res = 0;
        for (int x = i; x > 0; x -= x & -x)
            for (int y = j; y > 0; y -= y & -y)
                res += tree[x][y];
        return res;
    }
};

void solve() {
    // Point update, range query
    Fenwick2D_PointUpdate<int> fen(5, 5);
    fen.update(1, 1, 3);
    fen.update(2, 3, 5);
    fen.update(4, 4, 7);
    cout << "Sum of [1..3, 1..3]: " << fen.query(1, 1, 3, 3) << endl;  // 8

    // Range update, point query
    Fenwick2D_RangeUpdate<int> fen2(5, 5);
    fen2.update(1, 1, 3, 3, 4);
    fen2.update(2, 2, 4, 4, 2);
    cout << "Value at [2,2]: " << fen2.query(2, 2) << endl;  // 6
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
