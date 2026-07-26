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

// 2-SAT — O(V + E)
// Solves boolean satisfiability where each clause has exactly 2 literals
// Variables: x_0, x_1, ..., x_{n-1}
// Literal encoding: 2*i = x_i, 2*i+1 = not(x_i)
struct TwoSAT {
    int n;
    vector<vector<int>> adj, radj;
    vector<int> order, comp;
    vector<bool> visited;
    vector<bool> assignment;

    TwoSAT(int n) : n(n), adj(2 * n), radj(2 * n), comp(2 * n), visited(2 * n), assignment(n) {}

    // Add clause: (a OR b)
    // a, b are literal indices: 2*i for x_i, 2*i+1 for not(x_i)
    void add_clause(int a, int b) {
        adj[a ^ 1].push_back(b);  // not(a) -> b
        adj[b ^ 1].push_back(a);  // not(b) -> a
        radj[b].push_back(a ^ 1);
        radj[a].push_back(b ^ 1);
    }

    // Convenience: add (x_i = val_i) OR (x_j = val_j)
    void add_or(int i, bool val_i, int j, bool val_j) {
        add_clause(2 * i + val_i, 2 * j + val_j);
    }

    void dfs1(int u) {
        visited[u] = true;
        for (int v : adj[u])
            if (!visited[v]) dfs1(v);
        order.push_back(u);
    }

    void dfs2(int u, int c) {
        comp[u] = c;
        for (int v : radj[u])
            if (comp[v] == -1) dfs2(v, c);
    }

    // Returns true if satisfiable, fills assignment[]
    bool solve() {
        visited.assign(2 * n, false);
        order.clear();
        for (int i = 0; i < 2 * n; i++)
            if (!visited[i]) dfs1(i);

        comp.assign(2 * n, -1);
        int cnt = 0;
        for (int i = 2 * n - 1; i >= 0; i--) {
            int u = order[i];
            if (comp[u] == -1) dfs2(u, cnt++);
        }

        for (int i = 0; i < n; i++) {
            if (comp[2 * i] == comp[2 * i + 1]) return false;
            assignment[i] = comp[2 * i] > comp[2 * i + 1];
        }
        return true;
    }

    bool get_value(int i) { return assignment[i]; }
};

void solve() {
    // Example: (x0 OR x1) AND (NOT x0 OR x1) AND (x0 OR NOT x1)
    // Solution: x0 = true, x1 = true
    TwoSAT tsat(2);
    tsat.add_or(0, true, 1, true);    // x0 OR x1
    tsat.add_or(0, false, 1, true);   // !x0 OR x1
    tsat.add_or(0, true, 1, false);   // x0 OR !x1

    if (tsat.solve()) {
        cout << "SAT! x0=" << tsat.get_value(0) << " x1=" << tsat.get_value(1) << endl;
    } else {
        cout << "UNSAT" << endl;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
