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

// Min Cost Max Flow — O(min(E²V log V, E log V * flow))
// Works with negative costs (but not negative cycles)
struct MCMF {
    struct edge { int u, v, id; long long cap, cost; };
    int n, s, t;
    vector<vector<int>> g;
    vector<edge> e;
    vector<long long> d, potential;
    vector<int> par;
    long long flow, cost;

    MCMF(int n, int s, int t) : n(n+10), s(s), t(t), g(n+10),
        d(n+10), potential(n+10), par(n+10), flow(0), cost(0) {}

    void add_edge(int u, int v, long long cap, long long cost) {
        g[u].push_back(e.size());
        e.push_back({u, v, (int)e.size()+1, cap, cost});
        g[v].push_back(e.size());
        e.push_back({v, u, (int)e.size()-1, 0, -cost});
    }

    bool dijkstra() {
        fill(d.begin(), d.end(), LINF);
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> q;
        d[s] = 0; par[s] = -1;
        q.push({0, s});
        while (!q.empty()) {
            auto [nw, u] = q.top(); q.pop();
            if (nw != d[u]) continue;
            for (int id : g[u]) {
                auto& ed = e[id];
                long long w = ed.cost + potential[u] - potential[ed.v];
                if (d[u] + w < d[ed.v] && ed.cap > 0) {
                    d[ed.v] = d[u] + w;
                    par[ed.v] = id;
                    q.push({d[ed.v], ed.v});
                }
            }
        }
        for (int i = 0; i < n; i++)
            if (d[i] < LINF) potential[i] += d[i];
        return d[t] < LINF;
    }

    void augment() {
        long long f = LINF;
        for (int v = t; v != s; v = e[par[v]].u)
            f = min(f, e[par[v]].cap);
        for (int v = t; v != s; v = e[par[v]].u) {
            e[par[v]].cap -= f;
            e[e[par[v]].id].cap += f;
        }
        flow += f;
        cost += f * potential[t];
    }

    pair<long long, long long> solve() {
        while (dijkstra()) augment();
        return {flow, cost};
    }
};

void solve() {
    MCMF mcmf(4, 0, 3);
    mcmf.add_edge(0, 1, 10, 1);
    mcmf.add_edge(0, 2, 5, 2);
    mcmf.add_edge(1, 2, 15, 1);
    mcmf.add_edge(1, 3, 10, 3);
    mcmf.add_edge(2, 3, 10, 1);
    auto [f, c] = mcmf.solve();
    cout << "Max flow: " << f << ", Min cost: " << c << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
