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

// Closest Pair of Points — O(n log n)
// Divide and conquer approach
struct Point {
    int x, y, id;
};

long long min_dist;
pair<int,int> best_pair;

void update(const Point& p, const Point& q) {
    long long d = 1LL*(p.x-q.x)*(p.x-q.x) + 1LL*(p.y-q.y)*(p.y-q.y);
    if (d < min_dist) min_dist = d, best_pair = {p.id, q.id};
}

const int MAXN = 2e5 + 5;
Point pts[MAXN], tmp[MAXN];

void closest(int l, int r) {
    if (r - l <= 3) {
        sort(pts+l, pts+r, [](const Point& A, const Point& B) {
            return A.y == B.y ? A.x < B.x : A.y < B.y;
        });
        for (int i = l; i < r; i++)
            for (int j = l; j < i; j++)
                update(pts[i], pts[j]);
        return;
    }

    int m = (l + r) / 2;
    int midx = pts[m].x;
    closest(l, m);
    closest(m, r);

    merge(pts+l, pts+m, pts+m, pts+r, tmp+l,
        [](const Point& A, const Point& B) { return A.y == B.y ? A.x < B.x : A.y < B.y; });
    copy(tmp+l, tmp+r, pts+l);

    int top = -1;
    for (int i = l; r > i; i++) {
        if (abs(pts[i].x - midx) >= min_dist) continue;
        for (int j = top; j >= 0 && pts[i].y - tmp[j].y < min_dist; j--)
            update(pts[i], tmp[j]);
        tmp[++top] = pts[i];
    }
}

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> pts[i].x >> pts[i].y;
        pts[i].id = i;
    }

    min_dist = LINF;
    sort(pts, pts+n, [](const Point& A, const Point& B) {
        return A.x == B.x ? A.y < B.y : A.x < B.x;
    });

    closest(0, n);
    double dist = sqrt(min_dist);
    cout << fixed << setprecision(4) << dist << endl;
    cout << best_pair.first << " " << best_pair.second << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
