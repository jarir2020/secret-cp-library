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

// Stoer-Wagner Algorithm — O(n³)
// Finds the global minimum cut in an undirected weighted graph
struct StoerWagner {
    int n;
    vector<vector<long long>> G;
    vector<long long> dis;
    vector<int> idx;
    vector<bool> vis;

    StoerWagner(int _n) : n(_n), G(_n+1, vector<long long>(_n+1, 0)),
        dis(_n+1), idx(_n+1), vis(_n+1) {}

    void add_edge(int u, int v, long long w) {
        if (u != v) { G[u][v] += w; G[v][u] += w; }
    }

    long long solve() {
        long long ans = LINF;
        for (int i = 0; i < n; i++) idx[i] = i + 1;
        int cur = n;
        while (cur > 1) {
            int t = 1, s = 0;
            fill(vis.begin(), vis.end(), false);
            fill(dis.begin(), dis.end(), 0);
            vis[idx[0]] = true;
            for (int i = 1; i < cur; i++) {
                dis[idx[i]] = G[idx[0]][idx[i]];
                if (dis[idx[i]] > dis[idx[t]]) t = i;
            }
            for (int i = 1; i < cur; i++) {
                if (i == cur - 1) {
                    ans = min(ans, dis[idx[t]]);
                    if (ans == 0) return 0;
                    for (int j = 0; j < cur; j++) {
                        G[idx[s]][idx[j]] += G[idx[j]][idx[t]];
                        G[idx[j]][idx[s]] = G[idx[s]][idx[j]];
                    }
                    idx[t] = idx[--cur];
                }
                vis[idx[t]] = true;
                s = t; t = -1;
                for (int j = 1; j < cur; j++) {
                    if (!vis[idx[j]]) {
                        dis[idx[j]] += G[idx[s]][idx[j]];
                        if (t == -1 || dis[idx[t]] < dis[idx[j]]) t = j;
                    }
                }
            }
        }
        return ans;
    }
};

void solve() {
    StoerWagner sw(4);
    sw.add_edge(1, 2, 3); sw.add_edge(1, 3, 2);
    sw.add_edge(2, 3, 1); sw.add_edge(2, 4, 4); sw.add_edge(3, 4, 5);
    cout << "Global min cut: " << sw.solve() << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
