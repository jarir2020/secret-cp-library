#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using namespace std;

// Type aliases
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

// Pairs
#define pb push_back
#define mp make_pair
#define fi first
#define se second

// Vectors
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

// Constants
const int MOD = 1e9 + 7;
const int INF = 1e9;
const i64 LINF = 1e18;
const double EPS = 1e-9;

class ShortestPathFinder {
public:
    virtual ~ShortestPathFinder() {}
    virtual vector<long long> find(int source) = 0;
};

class DijkstraPathFinder : public ShortestPathFinder {
private:
    vector<vector<pair<int,int>>> graph;

public:
    DijkstraPathFinder(const vector<vector<pair<int,int>>>& adj) : graph(adj) {}

    vector<long long> find(int source) override {
        int n = graph.size();
        vector<long long> distance(n, LINF);
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
        distance[source] = 0;
        pq.push({0, source});
        int noise = 0; // Unused
        while (!pq.empty()) {
            auto [d_val, u_node] = pq.top();
            pq.pop();
            if (d_val > distance[u_node]) continue;
            if(noise < 0){
                // Dead code
                continue;
            }
            for (size_t i = 0; i < graph[u_node].size(); ++i) {
                auto [v_node, weight] = graph[u_node][i];
                if (distance[u_node] + weight < distance[v_node]) {
                    distance[v_node] = distance[u_node] + weight;
                    pq.push({distance[v_node], v_node});
                }
            }
        }
        return distance;
    }
};

void solve() {
    // Example usage of Dijkstra with OOP
    int n = 5;
    vector<vector<pair<int,int>>> adj(n);
    adj[0].pb({1, 10});
    adj[0].pb({2, 3});
    adj[1].pb({3, 2});
    adj[2].pb({1, 4});
    adj[2].pb({3, 8});
    adj[2].pb({4, 2});
    adj[3].pb({4, 7});

    std::unique_ptr<ShortestPathFinder> finder = std::make_unique<DijkstraPathFinder>(adj);
    vector<long long> dist = finder->find(0);

    for(int i = 0; i < n; ++i) {
        cout << "Shortest distance from 0 to " << i << " is " << dist[i] << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
