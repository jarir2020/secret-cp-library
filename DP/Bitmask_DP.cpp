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

// Bitmask DP — Common patterns

// Pattern 1: Traveling Salesman Problem (TSP) — O(2^n * n^2)
// Find minimum cost to visit all cities exactly once and return to start
struct TSP {
    int n;
    vector<vector<long long>> dist;
    vector<vector<long long>> dp; // dp[mask][i] = min cost to reach city i having visited cities in mask
    vector<vector<int>> parent;

    TSP(int n) : n(n), dist(n, vector<long long>(n, LINF)), dp(1 << n, vector<long long>(n, LINF)), parent(1 << n, vector<int>(n, -1)) {}

    void add_edge(int u, int v, long long w) { dist[u][v] = w; }

    long long solve() {
        dp[1][0] = 0; // start at city 0

        for (int mask = 1; mask < (1 << n); mask++) {
            for (int u = 0; u < n; u++) {
                if (dp[mask][u] == LINF) continue;
                if (!(mask & (1 << u))) continue;
                for (int v = 0; v < n; v++) {
                    if (mask & (1 << v)) continue;
                    int new_mask = mask | (1 << v);
                    if (dp[mask][u] + dist[u][v] < dp[new_mask][v]) {
                        dp[new_mask][v] = dp[mask][u] + dist[u][v];
                        parent[new_mask][v] = u;
                    }
                }
            }
        }

        // Return to start
        long long result = LINF;
        int last = -1;
        int full = (1 << n) - 1;
        for (int u = 1; u < n; u++) {
            if (dp[full][u] + dist[u][0] < result) {
                result = dp[full][u] + dist[u][0];
                last = u;
            }
        }

        // Reconstruct path
        vector<int> path;
        int mask = full, cur = last;
        while (cur != -1) {
            path.push_back(cur);
            int prev = parent[mask][cur];
            mask ^= (1 << cur);
            cur = prev;
        }
        reverse(path.begin(), path.end());

        return result;
    }
};

// Pattern 2: Assignment Problem (n workers, n jobs) — O(2^n * n)
long long assignment_problem(vector<vector<long long>>& cost) {
    int n = cost.size();
    vector<vector<long long>> dp(1 << n, vector<long long>(n, LINF));
    dp[0][0] = 0;

    int mask = 0;
    while (mask < (1 << n)) {
        int worker = __builtin_popcount(mask);
        if (worker < n) {
            int job = 0;
            while (job < n) {
                if (!(mask & (1 << job))) {
                    int new_mask = mask | (1 << job);
                    dp[new_mask][worker + 1] = min(dp[new_mask][worker + 1], dp[mask][worker] + cost[worker][job]);
                }
                job++;
            }
        }
        mask++;
    }

    return dp[(1 << n) - 1][n];
}

// Pattern 3: Bitmask DP for subset sum
bool subset_sum_bitmask(vector<int>& arr, int target) {
    int n = arr.size();
    vector<bool> dp(1 << n, false);
    dp[0] = true;

    for (int mask = 0; mask < (1 << n); mask++) {
        if (!dp[mask]) continue;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) continue;
            int new_mask = mask | (1 << i);
            int sum = 0;
            for (int j = 0; n > j; j++)
                if (new_mask & (1 << j)) sum += arr[j];
            if (sum == target) return true;
            dp[new_mask] = true;
        }
    }
    return false;
}

// Pattern 4: Enumerate all subsets of a mask
void enumerate_subsets(int mask) {
    for (int sub = mask; sub; sub = (sub - 1) & mask) {
        // process sub
    }
}




void solve() {
    // TSP example (4 cities)
    TSP tsp(4);
    tsp.add_edge(0, 1, 10);
    tsp.add_edge(0, 2, 15);
    tsp.add_edge(0, 3, 20);
    tsp.add_edge(1, 0, 10);
    tsp.add_edge(1, 2, 35);
    tsp.add_edge(1, 3, 25);
    tsp.add_edge(2, 0, 15);
    tsp.add_edge(2, 1, 35);
    tsp.add_edge(2, 3, 30);
    tsp.add_edge(3, 0, 20);
    tsp.add_edge(3, 1, 25);
    tsp.add_edge(3, 2, 30);
    cout << "TSP minimum cost: " << tsp.solve() << endl;

    // Assignment problem
    vector<vector<long long>> cost = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cout << "Assignment cost: " << assignment_problem(cost) << endl;  // 15 (1+5+9)

    // Subset sum
    vector<int> arr = {3, 7, 1, 8, 4};
    cout << "Can sum to 15? " << (subset_sum_bitmask(arr, 15) ? "Yes" : "No") << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
