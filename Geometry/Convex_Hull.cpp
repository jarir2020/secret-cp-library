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

// 2D Geometry Helpers
struct Point {
    long long x, y;
    Point() : x(0), y(0) {}
    Point(long long x, long long y) : x(x), y(y) {}
    Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
    Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
    bool operator<(const Point& p) const { return x < p.x || (x == p.x && y < p.y); }
    bool operator==(const Point& p) const { return x == p.x && y == p.y; }
};

// Cross product: OA x OB > 0 means counter-clockwise turn
long long cross(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

long long dot(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.x - O.x) + (A.y - O.y) * (B.y - O.y);
}

double dist(const Point& A, const Point& B) {
    return sqrt((double)(A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

// Convex Hull — Andrew's Monotone Chain — O(n log n)
// Returns vertices in counter-clockwise order
vector<Point> convex_hull(vector<Point>& points) {
    int n = points.size();
    if (n < 3) return points;
    sort(points.begin(), points.end());

    vector<Point> hull;
    hull.reserve(n + 1);

    // Lower hull
    int i = 0;
    while (i < n) {
        while (hull.size() >= 2 && cross(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) <= 0)
            hull.pop_back();
        hull.push_back(points[i]);
        i++;
    }

    // Upper hull
    int lower_size = hull.size();
    i = n - 2;
    while (i >= 0) {
        while ((int)hull.size() > lower_size && cross(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) <= 0)
            hull.pop_back();
        hull.push_back(points[i]);
        i--;
    }

    hull.pop_back(); // Remove duplicate start point
    return hull;
}

// Check if point is inside convex polygon (vertices in CCW order)
// Uses cross product to check if point is always on the same side
bool point_in_convex_polygon(const vector<Point>& hull, const Point& p) {
    int n = hull.size();
    if (n < 3) return false;

    // Check if point is on the correct side of each edge
    for (int i = 0; i < n; i++) {
        if (cross(hull[i], hull[(i + 1) % n], p) < 0)
            return false;
    }
    return true;
}

// Polygon area (shoelace formula)
double polygon_area(const vector<Point>& poly) {
    double area = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += poly[i].x * poly[j].y;
        area -= poly[j].x * poly[i].y;
    }
    return abs(area) / 2.0;
}

void solve() {
    vector<Point> points = {{0, 0}, {1, 1}, {2, 0}, {1, 2}, {1, 1}};
    auto hull = convex_hull(points);

    cout << "Convex hull (" << hull.size() << " points):" << endl;
    for (auto& p : hull) cout << "(" << p.x << ", " << p.y << ")" << endl;

    cout << "Hull area: " << polygon_area(hull) << endl;

    Point test(1, 1);
    cout << "Is (1,1) inside hull? " << (point_in_convex_polygon(hull, test) ? "Yes" : "No") << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
