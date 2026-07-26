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

// Gauss-Jordan Elimination — O(min(n,m) * n * m)
// Solves system of linear equations
// Returns: -1 = no solution, 0 = unique, >0 = number of free variables
template <class T>
int gauss(vector<vector<T>> eq, vector<T>& res, const T eps = 1e-12) {
    int n = eq.size(), m = eq[0].size() - 1;
    int i, j, k, l, p, f_var = 0;
    res.assign(m, 0);
    vector<int> pos(m, -1);

    for (j = 0, i = 0; j < m && i < n; j++) {
        for (k = i, p = i; k < n; k++)
            if (abs(eq[k][j]) > abs(eq[p][j])) p = k;
        if (abs(eq[p][j]) > eps) {
            pos[j] = i;
            for (l = j; l <= m; l++) swap(eq[p][l], eq[i][l]);
            for (k = 0; k < n; k++) {
                if (k != i) {
                    T x = eq[k][j] / eq[i][j];
                    for (l = j; l <= m; l++) eq[k][l] -= eq[i][l] * x;
                }
            }
            i++;
        }
    }

    for (i = 0; i < m; i++) {
        if (pos[i] == -1) f_var++;
        else res[i] = eq[pos[i]][m] / eq[pos[i]][i];
    }

    for (i = 0; i < n; i++) {
        T val = 0;
        for (j = 0; j < m; j++) val += res[j] * eq[i][j];
        if (abs(val - eq[i][m]) > eps) return -1;
    }

    return f_var;
}

void solve() {
    // 2x + y - z = 8, -3x -y + 2z = -11, -2x + y + 2z = -3
    vector<vector<double>> eq = {{2, 1, -1, 8}, {-3, -1, 2, -11}, {-2, 1, 2, -3}};
    vector<double> res;
    int result = gauss(eq, res);
    if (result == -1) cout << "No solution" << endl;
    else if (result == 0) {
        cout << "Unique solution: ";
        for (int i = 0; i < (int)res.size(); i++) cout << "x" << i << "=" << res[i] << " ";
        cout << endl;
    } else {
        cout << result << " free variables" << endl;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
