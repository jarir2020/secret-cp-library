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

// Convex Hull Trick (CHT) — O(n) amortized for monotonic queries
// For DP of form: dp[i] = min/max over j < i of { m[j] * x[i] + b[j] }
struct Line {
    long long m, b; // y = m*x + b
    mutable function<const Line*()> succ;
    bool operator<(const Line& other) const {
        if (other.b != INF) return m < other.m; // by slope for insertion
        // by intersection point for query
        long long dx = other.m - m;
        long long dy = b - other.b;
        if (dx == 0) return dy < 0;
        return dy < 0 ^ dx < 0; // careful with sign
    }
};

// Simpler CHT for monotonic queries (insert lines in order of slope)
// Supports: insert line with slope m, query at x
// Works for both min and max queries
struct SimpleCHT {
    struct Line { long long m, b; };
    deque<Line> hull;

    // Bad if intersection(a,b) >= intersection(b,c)
    bool bad(Line a, Line b, Line c) {
        // (b.b - a.b) / (a.m - b.m) >= (c.b - b.b) / (b.m - c.m)
        return (__int128)(c.b - b.b) * (a.m - b.m) <= (__int128)(b.b - a.b) * (b.m - c.m);
    }

    // For minimum: slopes in increasing order, query x in increasing order
    // For maximum: negate m and b, or reverse comparisons
    void add_line(long long m, long long b) {
        Line line = {m, b};
        while (hull.size() >= 2 && bad(hull[hull.size() - 2], hull.back(), line))
            hull.pop_back();
        hull.push_back(line);
    }

    long long query(long long x) {
        // Binary search on intersection points
        int lo = 0, hi = hull.size() - 1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (hull[mid].m * x + hull[mid].b > hull[mid + 1].m * x + hull[mid + 1].b)
                lo = mid + 1;
            else
                hi = mid;
        }
        return hull[lo].m * x + hull[lo].b;
    }
};

// Dynamic CHT using Li Chao Tree — O(log C) per insert and query
// Works for any order of insertions and queries
struct LiChaoTree {
    struct Line {
        long long m = 0, b = -LINF;
        long long eval(long long x) { return m * x + b; }
    };

    struct Node {
        Line line;
        Node *l = nullptr, *r = nullptr;
    }*root;
    long long lo, hi;

    LiChaoTree(long long lo, long long hi) : lo(lo), hi(hi) { root = new Node(); }

    void insert(Line new_line, Node* node, long long l, long long r) {
        long long mid = (l + r) >> 1;
        bool leftBetter = new_line.eval(l) > node->line.eval(l);
        bool midBetter = new_line.eval(mid) > node->line.eval(mid);

        if (midBetter) swap(node->line, new_line);

        if (r - l == 1) return;

        if (leftBetter != midBetter) {
            if (!node->l) node->l = new Node();
            insert(new_line, node->l, l, mid);
        } else {
            if (!node->r) node->r = new Node();
            insert(new_line, node->r, mid, r);
        }
    }

    void add_line(long long m, long long b) {
        insert({m, b}, root, lo, hi);
    }

    long long query(long long x, Node* node, long long l, long long r) {
        if (!node) return -LINF;
        long long res = node->line.eval(x);
        if (r - l == 1) return res;
        long long mid = (l + r) >> 1;
        if (x < mid) return max(res, query(x, node->l, l, mid));
        return max(res, query(x, node->r, mid, r));
    }

    long long query(long long x) { return query(x, root, lo, hi); }
};

void solve() {
    // Example: minimize y = m*x + b for various lines
    SimpleCHT cht;
    cht.add_line(1, 0);   // y = x
    cht.add_line(-1, 10);  // y = -x + 10
    cht.add_line(2, -5);   // y = 2x - 5

    cout << "Min at x=3: " << cht.query(3) << endl;  // min(3, 7, 1) = 1
    cout << "Min at x=5: " << cht.query(5) << endl;  // min(5, 5, 5) = 5

    // Li Chao Tree example
    LiChaoTree lct(-1e6, 1e6);
    lct.add_line(1, 0);    // y = x
    lct.add_line(-1, 10);  // y = -x + 10
    lct.add_line(2, -5);   // y = 2x - 5

    cout << "LiChao max at x=3: " << lct.query(3) << endl; // max(3, 7, 1) = 7
    cout << "LiChao max at x=5: " << lct.query(5) << endl; // max(5, 5, 5) = 5
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
