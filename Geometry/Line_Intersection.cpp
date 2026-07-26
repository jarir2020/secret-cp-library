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

// Line intersection — O(1)
// Lines: a1*x + b1*y = c1  and  a2*x + b2*y = c2
// Returns {x, y} if unique intersection, or signals parallel/coincident
struct LineIntersection {
    struct Result {
        bool exists;
        bool parallel;
        bool coincident;
        double x, y;
    };

    static Result intersect(double a1, double b1, double c1, double a2, double b2, double c2) {
        double det = a1 * b2 - a2 * b1;
        Result res;
        res.exists = true;
        res.parallel = false;
        res.coincident = false;

        if (abs(det) < 1e-9) {
            // Parallel or coincident
            double cross = a1 * c2 - a2 * c1;
            if (abs(cross) < 1e-9) {
                res.coincident = true; // infinitely many solutions
            } else {
                res.parallel = true;   // no intersection
                res.exists = false;
            }
        } else {
            res.x = (c1 * b2 - c2 * b1) / det;
            res.y = (a1 * c2 - a2 * c1) / det;
        }
        return res;
    }
};

// Line intersection using cross products — integer arithmetic
// More precise, no floating point errors
struct Point {
    long long x, y;
    Point() : x(0), y(0) {}
    Point(long long x, long long y) : x(x), y(y) {}
    Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
};

long long cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

// Check if point c is on segment ab
bool on_segment(Point a, Point b, Point c) {
    if (cross(b - a, c - a) != 0) return false;
    return min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y);
}

// Find intersection of segments ab and cd
// Returns: 0=no intersection, 1=point, 2=segment (collinear overlap)
int segment_intersection(Point a, Point b, Point c, Point d, Point& result) {
    long long d1 = cross(b - a, c - a);
    long long d2 = cross(b - a, d - a);
    long long d3 = cross(d - c, a - c);
    long long d4 = cross(d - c, b - c);

    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
        ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) {
        // Proper intersection — use cross ratio to find point
        double t = (double)(d3) / (d3 - d4);
        result = {a.x + (long long)round(t * (b.x - a.x)),
                  a.y + (long long)round(t * (b.y - a.y))};
        return 1;
    }

    // Check collinear cases
    if (d1 == 0 && on_segment(a, b, c)) { result = c; return 1; }
    if (d2 == 0 && on_segment(a, b, d)) { result = d; return 1; }
    if (d3 == 0 && on_segment(c, d, a)) { result = a; return 1; }
    if (d4 == 0 && on_segment(c, d, b)) { result = b; return 1; }

    return 0;
}

// Closest point on segment ab to point p
Point closest_point_on_segment(Point a, Point b, Point p) {
    Point ab = b - a;
    Point ap = p - a;
    double t = (double)(ab.x * ap.x + ab.y * ap.y) / (ab.x * ab.x + ab.y * ab.y);
    t = max(0.0, min(1.0, t));
    return {a.x + (long long)round(t * ab.x), a.y + (long long)round(t * ab.y)};
}

// Distance from point p to line through a and b
double point_to_line_distance(Point p, Point a, Point b) {
    Point ab = b - a;
    Point ap = p - a;
    return abs((double)cross(ab, ap)) / sqrt((double)(ab.x * ab.x + ab.y * ab.y));
}

void solve() {
    // Line intersection
    auto res = LineIntersection::intersect(1, 1, 5, 2, -1, 1);
    cout << "Intersection: (" << res.x << ", " << res.y << ")" << endl;  // (2, 3)

    // Segment intersection
    Point a(0, 0), b(10, 10), c(0, 10), d(10, 0), result;
    int type = segment_intersection(a, b, c, d, result);
    if (type == 1) cout << "Intersection at (" << result.x << ", " << result.y << ")" << endl;

    // Point to line distance
    Point p(3, 1), l1(0, 0), l2(4, 0);
    cout << "Distance: " << point_to_line_distance(p, l1, l2) << endl;  // 1.0

    // Closest point on segment
    Point closest = closest_point_on_segment({0, 0}, {10, 0}, {5, 5});
    cout << "Closest point: (" << closest.x << ", " << closest.y << ")" << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
