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

struct Point {
    long long x, y;
    Point() : x(0), y(0) {}
    Point(long long x, long long y) : x(x), y(y) {}
    Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
    bool operator<(const Point& p) const { return x < p.x || (x == p.x && y < p.y); }
};

long long cross(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

long long dot(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.x - O.x) + (A.y - O.y) * (B.y - O.y);
}

// Point in Polygon — Ray casting algorithm — O(n)
// Returns: 0 = outside, 1 = inside, 2 = on boundary
int point_in_polygon(const vector<Point>& poly, const Point& p) {
    int n = poly.size();
    int inside = 0;
    int i = 0;
    while (i < n) {
        int j = (i + 1) % n;
        Point a = poly[i], b = poly[j];

        // Check if point is on the segment
        if (cross(a, b, p) == 0 && dot(a, p, b) >= 0) return 2;

        // Ray casting
        bool cond1 = (a.y > p.y) != (b.y > p.y);
        if (cond1) {
            double x_intersect = a.x + (double)(b.x - a.x) * (p.y - a.y) / (b.y - a.y);
            if (p.x < x_intersect) inside ^= 1;
        }
        i++;
    }
    return inside;
}

// Line intersection check
// Returns true if segments ab and cd intersect (including endpoints)
bool segments_intersect(Point a, Point b, Point c, Point d) {
    long long d1 = cross(c, d, a);
    long long d2 = cross(c, d, b);
    long long d3 = cross(a, b, c);
    long long d4 = cross(a, b, d);

    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
        ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
        return true;

    if (d1 == 0 && dot(c, a, d) >= 0) return true;
    if (d2 == 0 && dot(c, b, d) >= 0) return true;
    if (d3 == 0 && dot(a, c, b) >= 0) return true;
    if (d4 == 0 && dot(a, d, b) >= 0) return true;

    return false;
}

// Angle from point O to point A
double angle(const Point& O, const Point& A) {
    return atan2(A.y - O.y, A.x - O.x);
}

// Orientation test: returns +1 (CCW), -1 (CW), 0 (collinear)
int orientation(Point p, Point q, Point r) {
    long long val = cross(p, q, r);
    if (val > 0) return 1;   // CCW
    if (val < 0) return -1;  // CW
    return 0;                 // collinear
}

void solve() {
    // Point in polygon test
    vector<Point> poly = {{0, 0}, {10, 0}, {10, 10}, {0, 10}};
    Point inside(5, 5), outside(15, 5), boundary(0, 5);

    auto check = [](int result) {
        return result == 0 ? "outside" : (result == 1 ? "inside" : "boundary");
    };

    cout << "(5,5): " << check(point_in_polygon(poly, inside)) << endl;
    cout << "(15,5): " << check(point_in_polygon(poly, outside)) << endl;
    cout << "(0,5): " << check(point_in_polygon(poly, boundary)) << endl;

    // Segment intersection
    Point a(0, 0), b(10, 10), c(0, 10), d(10, 0);
    cout << "Segments intersect? " << (segments_intersect(a, b, c, d) ? "Yes" : "No") << endl;

    // Orientation
    Point p(0, 0), q(1, 1), r(2, 0);
    int o = orientation(p, q, r);
    cout << "Orientation: " << (o == 1 ? "CCW" : (o == -1 ? "CW" : "collinear")) << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
