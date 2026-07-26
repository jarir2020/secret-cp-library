#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using namespace std;

// Type aliases
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

// Constants
const int MOD = 1e9 + 7;
const int INF = 1e9;
const i64 LINF = 1e18;
const double EPS = 1e-9;

// Segment Tree — Point Update + Range Query — O(log n) per operation
// Template version supporting min, max, sum via merge function
template<typename T>
struct SegmentTree {
    int n;
    vector<T> tree;
    T default_val;

    // Merge function — change this for different queries
    // For min: return min(a, b);
    // For max: return max(a, b);
    // For sum: return a + b;
    // For gcd: return __gcd(a, b);
    static T merge(T a, T b) {
        return max(a, b);  // Change to min/max/sum/gcd as needed
    }

    SegmentTree(int n, T default_val = 0) : n(n), tree(4 * n, default_val), default_val(default_val) {}

    SegmentTree(vector<T>& arr) : n(arr.size()), tree(4 * arr.size()) {
        build(arr, 1, 0, n - 1);
    }

    void build(vector<T>& arr, int node, int l, int r) {
        if (l == r) {
            tree[node] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, node * 2, l, mid);
        build(arr, node * 2 + 1, mid + 1, r);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int pos, T val, int node = 1, int l = 0, int r = -1) {
        if (r == -1) r = n - 1;
        if (l == r) {
            tree[node] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) update(pos, val, node * 2, l, mid);
        else update(pos, val, node * 2 + 1, mid + 1, r);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    T query(int ql, int qr, int node = 1, int l = 0, int r = -1) {
        if (r == -1) r = n - 1;
        if (qr < l || ql > r) return default_val;
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return merge(query(ql, qr, node * 2, l, mid),
                     query(ql, qr, node * 2 + 1, mid + 1, r));
    }
};

// Persistent Segment Tree — O(log n) per operation, O(n log n) space
// Useful for k-th element queries, offline range queries
struct PersistentSegTree {
    struct Node {
        int left, right;
        long long sum;
    };

    int n, root;
    vector<Node> tree;
    vector<int> roots; // roots[i] = root of version i

    PersistentSegTree(int n) : n(n), root(0) {
        tree.push_back({0, 0, 0}); // null node
        roots.push_back(build(1, n));
    }

    int build(int l, int r) {
        int node = tree.size();
        tree.push_back({0, 0, 0});
        if (l == r) return node;
        int mid = (l + r) / 2;
        tree[node].left = build(l, mid);
        tree[node].right = build(mid + 1, r);
        return node;
    }

    int update(int prev, int l, int r, int pos, long long val) {
        int node = tree.size();
        tree.push_back(tree[prev]);
        if (l == r) {
            tree[node].sum += val;
            return node;
        }
        int mid = (l + r) / 2;
        if (pos <= mid)
            tree[node].left = update(tree[prev].left, l, mid, pos, val);
        else
            tree[node].right = update(tree[prev].right, mid + 1, r, pos, val);
        tree[node].sum = tree[tree[node].left].sum + tree[tree[node].right].sum;
        return node;
    }

    void add_version(int pos, long long val) {
        roots.push_back(update(roots.back(), 1, n, pos, val));
    }

    long long query(int version, int ql, int qr) {
        return query(roots[version], 1, n, ql, qr);
    }

    long long query(int node, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) return 0;
        if (ql <= l && r <= qr) return tree[node].sum;
        int mid = (l + r) / 2;
        return query(tree[node].left, l, mid, ql, qr) +
               query(tree[node].right, mid + 1, r, ql, qr);
    }

    // Find k-th smallest element in range [ql..qr] — O(log n)
    int kth(int ver_l, int ver_r, int l, int r, int k) {
        if (l == r) return l;
        int mid = (l + r) / 2;
        int left_count = tree[tree[ver_r].left].sum - tree[tree[ver_l].left].sum;
        if (k <= left_count)
            return kth(tree[ver_l].left, tree[ver_r].left, l, mid, k);
        else
            return kth(tree[ver_l].right, tree[ver_r].right, mid + 1, r, k - left_count);
    }
};

void solve() {
    // Basic segment tree example
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree<int> st(arr);

    cout << "Max of [1..4]: " << st.query(1, 4) << endl;  // 9
    st.update(2, 10); // arr[2] = 10
    cout << "After update, max of [1..4]: " << st.query(1, 4) << endl;  // 10

    // Persistent segment tree example
    PersistentSegTree pst(10);
    pst.add_version(3, 1); // version 1: add 3
    pst.add_version(1, 1); // version 2: add 1
    pst.add_version(4, 1); // version 3: add 4
    pst.add_version(1, 1); // version 4: add 1 again

    cout << "Sum in version 4, range [1..5]: " << pst.query(4, 1, 5) << endl;  // 9
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
