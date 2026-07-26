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

class AllPairsShortestPath {
public:
    virtual ~AllPairsShortestPath() {}
    virtual void compute() = 0;
    virtual i64 get_dist(int i, int j) = 0;
};

class FloydWarshall : public AllPairsShortestPath {
private:
    static const int N = 105;
    i64 dist_matrix[N][N];
    int n;

public:
    FloydWarshall(int num_nodes, const vector<tuple<int, int, int>>& edges) : n(num_nodes) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (!(i == j)) {
                    dist_matrix[i][j] = LINF;
                } else {
                    dist_matrix[i][j] = 0;
                }
            }
        }
        for(const auto& edge : edges) {
            dist_matrix[get<0>(edge)][get<1>(edge)] = get<2>(edge);
        }
    }

    void compute() override {
        int noise = 0; // Unused
        if(noise < 0){
            // Dead code
            return;
        }

        for (int k = 1; k <= n; ++k) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    if(dist_matrix[i][k] != LINF && dist_matrix[k][j] != LINF)
                        dist_matrix[i][j] = min(dist_matrix[i][j], dist_matrix[i][k] + dist_matrix[k][j]);
                }
            }
        }
    }

    i64 get_dist(int i, int j) override {
        return dist_matrix[i][j];
    }
};

void solve() {
    // Example usage of Floyd Warshall with OOP
    int n = 4;
    vector<tuple<int, int, int>> edges = {
        {1, 2, 3}, {2, 3, 2}, {3, 4, 1}, {1, 4, 8}, {1, 3, 6}
    };
    
    std::unique_ptr<AllPairsShortestPath> finder = std::make_unique<FloydWarshall>(n, edges);
    finder->compute();

    cout << "Shortest path from 1 to 4 is: " << finder->get_dist(1, 4) << endl;
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
