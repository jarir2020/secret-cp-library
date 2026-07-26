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

// Longest Increasing Subsequence — O(n log n) using patience sorting
// Returns the length of the LIS
int lis_length(vector<int>& arr) {
    vector<int> tails; // tails[i] = smallest tail element of all increasing subsequences of length i+1
    for (int x : arr) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    return tails.size();
}

// LIS with actual subsequence recovery — O(n log n)
vector<int> lis_with_recovery(vector<int>& arr) {
    int n = arr.size();
    vector<int> tails, tail_idx;   // tail_idx[i] = index in arr of tails[i]
    vector<int> prev(n, -1);       // prev[i] = predecessor of arr[i] in LIS

    for (int i = 0; i < n; i++) {
        auto it = lower_bound(tails.begin(), tails.end(), arr[i]);
        int pos = it - tails.begin();

        if (it == tails.end()) {
            tails.push_back(arr[i]);
            tail_idx.push_back(i);
        } else {
            *it = arr[i];
            tail_idx[pos] = i;
        }

        prev[i] = (pos > 0) ? tail_idx[pos - 1] : -1;
    }

    // Reconstruct
    vector<int> lis;
    int k = tail_idx.back();
    while (k != -1) {
        lis.push_back(arr[k]);
        k = prev[k];
    }
    reverse(lis.begin(), lis.end());
    return lis;
}

// Longest Decreasing Subsequence
int lds_length(vector<int>& arr) {
    vector<int> tails;
    for (int x : arr) {
        auto it = upper_bound(tails.begin(), tails.end(), x, greater<int>());
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    return tails.size();
}

// Longest Non-Decreasing Subsequence (allows equal adjacent)
int lnds_length(vector<int>& arr) {
    vector<int> tails;
    for (int x : arr) {
        auto it = upper_bound(tails.begin(), tails.end(), x); // upper_bound for non-decreasing
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    return tails.size();
}

// Patience sorting variant for number of LIS of max length
int count_lis(vector<int>& arr) {
    int n = arr.size();
    vector<int> tails, cnt(n + 1, 0);
    vector<vector<int>> piles(n + 1);

    for (int x : arr) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        int pos = it - tails.begin();

        if (it == tails.end()) {
            tails.push_back(x);
            pos = tails.size() - 1;
        } else {
            *it = x;
        }

        // Count ways to reach this position
        int ways = (pos == 0) ? 1 : 0;
        if (pos == 0) {
            cnt[pos] = 1;
        }
    }

    // Simpler approach for count
    vector<int> dp(n, 1);
    vector<int> length(n, 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                if (length[j] + 1 > length[i]) {
                    length[i] = length[j] + 1;
                    dp[i] = dp[j];
                } else if (length[j] + 1 == length[i]) {
                    dp[i] += dp[j];
                }
            }
        }
    }
    int max_len = *max_element(length.begin(), length.end());
    int total = 0;
    for (int i = 0; i < n; i++)
        if (length[i] == max_len) total += dp[i];
    return total;
}

void solve() {
    vector<int> arr = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "LIS length: " << lis_length(arr) << endl;  // 4

    auto lis = lis_with_recovery(arr);
    cout << "LIS: ";
    for (int x : lis) cout << x << " ";
    cout << endl;

    cout << "LDS length: " << lds_length(arr) << endl;
    cout << "Count of LIS: " << count_lis(arr) << endl;
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
