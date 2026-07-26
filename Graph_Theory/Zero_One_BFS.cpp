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

// 0-1 BFS — O(V + E)
// Shortest path on graph where edges have weight 0 or 1
// Uses deque: push_front for 0-weight, push_back for 1-weight
struct ZeroOneBFS {
    int n;
    vector<vector<pair<int,int>>> adj; // {neighbor, weight(0 or 1)}
    vector<int> dist;

    ZeroOneBFS(int n) : n(n), adj(n), dist(n, INF) {}

    void add_edge(int u, int v, int w) { adj[u].push_back({v, w}); }

    void run(int source) {
        deque<int> dq;
        dist[source] = 0;
        dq.push_front(source);

        while (!dq.empty()) {
            int u = dq.front(); dq.pop_front();
            for (auto& [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    if (w == 0) dq.push_front(v);
                    else dq.push_back(v);
                }
            }
        }
    }
};

// Multisource BFS — O(V + E)
// BFS from multiple sources simultaneously
// Useful for: nearest source, flood fill, distance to closest special node
struct MultisourceBFS {
    int n;
    vector<vector<int>> adj;
    vector<int> dist;

    MultisourceBFS(int n) : n(n), adj(n), dist(n, INF) {}

    void add_edge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }

    void run(vector<int>& sources) {
        queue<int> q;
        for (int s : sources) { dist[s] = 0; q.push(s); }

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (dist[v] == INF) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
    }
};

void solve() {
    // 0-1 BFS
    ZeroOneBFS bfs(5);
    bfs.add_edge(0, 1, 0);
    bfs.add_edge(0, 2, 1);
    bfs.add_edge(1, 3, 1);
    bfs.add_edge(2, 3, 0);
    bfs.add_edge(3, 4, 0);
    bfs.run(0);
    cout << "0-1 BFS dist to 4: " << bfs.dist[4] << endl;  // 1

    // Multisource BFS
    MultisourceBFS mbfs(6);
    mbfs.add_edge(0, 1); mbfs.add_edge(1, 2); mbfs.add_edge(2, 3);
    mbfs.add_edge(3, 4); mbfs.add_edge(4, 5);
    vector<int> sources = {0, 5};
    mbfs.run(sources);
    cout << "Multisource dist[3]: " << mbfs.dist[3] << endl;  // 2
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
