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

// Sum Over Subsets (SOS) DP — O(n * 2^n)
// For a function f on bitmasks, compute F[mask] = sum of f[sub] for all sub ⊆ mask

// SOS DP — sum over subsets (forward)
// f[mask] = sum of f[sub] for all sub ⊆ mask
void sos_sum_subsets(vector<long long>& f) {
    int n = __builtin_ctz(f.size()); // number of bits
    int i = 0;
    while (i < n) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if (mask & (1 << i))
                f[mask] += f[mask ^ (1 << i)];
        }
        i++;
    }
}

// SOS DP — sum over supersets (reverse)
// f[mask] = sum of f[sup] for all sup ⊇ mask
void sos_sum_supersets(vector<long long>& f) {
    int n = __builtin_ctz(f.size());
    int i = 0;
    while (i < n) {
        int mask = (1 << n) - 1;
        while (mask >= 0) {
            if (mask & (1 << i))
                f[mask ^ (1 << i)] += f[mask];
            mask--;
        }
        i++;
    }
}

// SOS DP — sum over subsets with exactly k bits set
// Uses zeta transform approach
vector<vector<long long>> sos_k_bits(vector<long long>& f, int max_k) {
    int n = __builtin_ctz(f.size());
    int K = max_k;
    // dp[mask][k] = sum of f[sub] where sub ⊆ mask and popcount(sub) = k
    vector<vector<long long>> dp(1 << n, vector<long long>(K + 1, 0));

    // Initialize
    for (int mask = 0; mask < (1 << n); mask++) {
        int pc = __builtin_popcount(mask);
        if (pc <= K) dp[mask][pc] = f[mask];
    }

    // SOS DP per bit count
    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if (mask & (1 << i)) {
                for (int k = 0; k <= K; k++) {
                    dp[mask][k] += dp[mask ^ (1 << i)][k];
                }
            }
        }
    }
    return dp;
}

// Example: count pairs with OR equal to mask
// Given array a, for each mask compute cnt[mask] = number of pairs (i,j) where (a[i] | a[j]) == mask
void count_or_pairs(vector<int>& a, vector<long long>& cnt) {
    int n = a.size();
    int bits = 20; // assuming values up to 2^20
    vector<long long> freq(1 << bits, 0);
    for (int x : a) freq[x]++;

    // SOS DP for superset sums
    sos_sum_supersets(freq);

    // For each mask, number of pairs with OR ⊆ mask is freq[mask] * (freq[mask] - 1) / 2
    // Use inclusion-exclusion to get exact OR = mask
    for (int mask = (1 << bits) - 1; mask >= 0; mask--) {
        cnt[mask] = freq[mask] * (freq[mask] - 1) / 2;
        for (int i = 0; i < bits; i++) {
            if (mask & (1 << i)) {
                cnt[mask] -= cnt[mask ^ (1 << i)];
            }
        }
    }
}




void solve() {
    // SOS DP example
    int n = 3; // 3 bits
    vector<long long> f(1 << n, 0);
    f[0b001] = 1;
    f[0b010] = 2;
    f[0b100] = 3;
    f[0b011] = 4;

    vector<long long> F = f;
    sos_sum_subsets(F);

    cout << "SOS DP (sum over subsets):" << endl;
    for (int mask = 0; mask < (1 << n); mask++) {
        cout << "F[" << mask << "] = " << F[mask] << endl;
    }

    // Verify: F[0b011] = f[0] + f[001] + f[010] + f[011] = 0 + 1 + 2 + 4 = 7
    cout << "F[3] = " << F[3] << " (expected 7)" << endl;
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
