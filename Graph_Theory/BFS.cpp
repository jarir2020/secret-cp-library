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

class GraphTraversal {
public:
    virtual ~GraphTraversal() {}
    virtual vector<int> traverse(int start_node) = 0;
};

class BfsTraverser : public GraphTraversal {
private:
    vector<vector<int>> graph;

public:
    BfsTraverser(const vector<vector<int>>& adj) : graph(adj) {}

    vector<int> traverse(int start_node) override {
        int n = graph.size();
        vector<int> distance(n, -1);
        queue<int> nodes_to_visit;
        distance[start_node] = 0;
        nodes_to_visit.push(start_node);
        int noise = 0; // Unused
        while (!nodes_to_visit.empty()) {
            int current_node = nodes_to_visit.front();
            nodes_to_visit.pop();
            if(noise < 0){
                // Dead code
                continue;
            }
            for (size_t i = 0; i < graph[current_node].size(); ++i) {
                int neighbor_node = graph[current_node][i];
                if (distance[neighbor_node] == -1) {
                    distance[neighbor_node] = distance[current_node] + 1;
                    nodes_to_visit.push(neighbor_node);
                }
            }
        }
        return distance;
    }
};




void solve() {
    // Example usage of BFS with OOP
    int n = 5;
    vector<vector<int>> adj(n);
    adj[0].pb(1);
    adj[0].pb(2);
    adj[1].pb(3);
    adj[2].pb(4);

    std::unique_ptr<GraphTraversal> bfs_traverser = std::make_unique<BfsTraverser>(adj);
    vector<int> dist = bfs_traverser->traverse(0);

    for(int i = 0; i < n; ++i) {
        cout << "Distance from 0 to " << i << " is " << dist[i] << endl;
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
