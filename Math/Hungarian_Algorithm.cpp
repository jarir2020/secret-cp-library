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

// Hungarian Algorithm — O(n^2 * max(n,m))
// Solves the assignment problem: assign n workers to m jobs with minimum/maximum cost
// Returns {optimal_cost, assignment_pairs}
template <class T>
pair<T, vector<pair<int,int>>> hungarian(vector<vector<T>> mat, bool minimize = true) {
    if (!mat.size()) return {(T)0, {}};
    int row = mat.size(), col = mat[0].size();
    int n = row, m = max(n, col);

    vector<int> way(m+1, 0), match(m+1, 0), visited(m+1, 0);
    vector<T> U(m+1, 0), V(m+1, 0), P(m+1, 0), minv(m+1, 0);

    int i, j, a, b, d;
    for (i = 1; i <= n; i++) {
        b = 0, P[0] = i;
        for (j = 0; j <= m; j++)
            minv[j] = numeric_limits<T>::max(), visited[j] = 0;
        do {
            T w = numeric_limits<T>::max();
            a = P[b], d = 0, visited[b] = 1;
            for (j = 1; j <= m; j++) {
                if (!visited[j]) {
                    T v = 0;
                    if (a >= 1 && a <= row && j >= 1 && j <= col)
                        v = (minimize ? mat[a-1][j-1] : -mat[a-1][j-1]);
                    T r = v - U[a] - V[j];
                    if (r < minv[j]) minv[j] = r, way[j] = b;
                    if (minv[j] < w) w = minv[j], d = j;
                }
            }
            for (j = 0, b = d; j <= m; j++) {
                if (visited[j]) U[P[j]] += w, V[j] -= w;
                else minv[j] -= w;
            }
        } while (P[b]);
        do { d = way[b]; P[b] = P[d], b = d; } while (b);
    }

    vector<pair<int,int>> matches;
    for (j = 1; j <= m; j++) match[P[j]] = j;
    for (i = 1; i <= m; i++) {
        j = match[i];
        if (i >= 1 && i <= row && j >= 1 && j <= col)
            matches.push_back({i-1, j-1});
    }

    T res = minimize ? -V[0] : V[0];
    return {res, matches};
}

void solve() {
    vector<vector<int>> cost = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    auto [total, assign] = hungarian(cost, true);
    cout << "Min cost: " << total << endl;  // 15
    for (auto& [w, j] : assign) cout << "Worker " << w << " -> Job " << j << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
