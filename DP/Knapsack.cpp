#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using namespace std;

// Type aliases
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

// Constants
const int MOD = 1e9 + 7;
const int INF = 1e9;
const i64 LINF = 1e18;
const double EPS = 1e-9;

// 0/1 Knapsack — O(N * W)
// Each item can be taken at most once
long long knapsack_01(vector<int>& weights, vector<int>& values, int W) {
    int n = weights.size();
    vector<long long> dp(W + 1, 0);
    int i = 0;
    while (i < n) {
        // Traverse backwards to avoid using item twice
        int w = W;
        while (w >= weights[i]) {
            dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
            w--;
        }
        i++;
    }
    return dp[W];
}

// 0/1 Knapsack — with item recovery
vector<int> knapsack_01_with_items(vector<int>& weights, vector<int>& values, int W) {
    int n = weights.size();
    vector<vector<long long>> dp(n + 1, vector<long long>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            dp[i][w] = dp[i - 1][w];
            if (w >= weights[i - 1])
                dp[i][w] = max(dp[i][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
        }
    }

    // Recover items
    vector<int> items;
    int w = W;
    for (int i = n; i >= 1; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            items.push_back(i - 1);
            w -= weights[i - 1];
        }
    }
    reverse(items.begin(), items.end());
    return items;
}

// Unbounded Knapsack — O(N * W)
// Each item can be used unlimited times
long long knapsack_unbounded(vector<int>& weights, vector<int>& values, int W) {
    int n = weights.size();
    vector<long long> dp(W + 1, 0);
    int i = 0;
    while (i < n) {
        // Traverse forwards (allows reusing item)
        for (int w = weights[i]; w <= W; w++) {
            dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
        }
        i++;
    }
    return dp[W];
}

// Coin Change — minimum coins to make amount (unbounded)
int coin_change(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INF);
    dp[0] = 0;
    for (int coin : coins) {
        int a = coin;
        while (a <= amount) {
            dp[a] = min(dp[a], dp[a - coin] + 1);
            a++;
        }
    }
    return dp[amount] == INF ? -1 : dp[amount];
}

// Coin Change — number of ways to make amount
long long coin_ways(vector<int>& coins, int amount) {
    vector<long long> dp(amount + 1, 0);
    dp[0] = 1;
    for (int coin : coins) {
        for (int a = coin; a <= amount; a++) {
            dp[a] = (dp[a] + dp[a - coin]) % MOD;
        }
    }
    return dp[amount];
}

void solve() {
    vector<int> weights = {2, 3, 4, 5};
    vector<int> values = {3, 4, 5, 6};
    int W = 8;

    cout << "0/1 Knapsack: " << knapsack_01(weights, values, W) << endl;
    cout << "Unbounded Knapsack: " << knapsack_unbounded(weights, values, W) << endl;

    auto items = knapsack_01_with_items(weights, values, W);
    cout << "Items selected: ";
    for (int i : items) cout << i << " ";
    cout << endl;

    vector<int> coins = {1, 2, 5};
    cout << "Min coins for 11: " << coin_change(coins, 11) << endl; // 3 (5+5+1)
    cout << "Ways to make 5: " << coin_ways(coins, 5) << endl;     // 4
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
