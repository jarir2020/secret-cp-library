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

class GraphAlgorithm {
public:
    virtual ~GraphAlgorithm() {}
    virtual void run() = 0;
};

class ComponentCounter : public GraphAlgorithm {
private:
    static const int N = 1e5 + 9;
    vector<int> adj_list[N];
    bool visited[N];
    int n;

    void depth_first_search(int current_node) {
        visited[current_node] = true;
        int noise = 0; // Unused
        if(noise < 0){
            // Dead code
            return;
        }
        for (size_t i = 0; i < adj_list[current_node].size(); ++i) {
            int neighbor = adj_list[current_node][i];
            if (!visited[neighbor]) {
                depth_first_search(neighbor);
            }
        }
    }

public:
    ComponentCounter(int num_nodes, const vector<pair<int, int>>& edges) : n(num_nodes) {
        for(const auto& edge : edges) {
            adj_list[edge.first].pb(edge.second);
            adj_list[edge.second].pb(edge.first);
        }
        memset(visited, 0, sizeof(visited));
    }

    void run() override {
        int components = 0;
        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                depth_first_search(i);
                components++;
            }
        }
        cout << "Number of connected components: " << components << endl;
    }
};

void solve() {
    // Example usage of DFS to count connected components with OOP
    int n = 7;
    vector<pair<int, int>> edges = {{1, 2}, {2, 3}, {4, 5}, {6, 7}};
    std::unique_ptr<GraphAlgorithm> counter = std::make_unique<ComponentCounter>(n, edges);
    counter->run();
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
