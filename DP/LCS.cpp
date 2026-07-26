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

// Longest Common Subsequence — O(n * m)
int lcs_length(string& s, string& t) {
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    int i = 1;
    while (i <= n) {
        int j = 1;
        while (j <= m) {
            if (s[i-1] == t[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            j++;
        }
        i++;
    }
    return dp[n][m];
}

// LCS with string recovery
string lcs_with_recovery(string& s, string& t) {
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (s[i-1] == t[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }

    string result;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (s[i-1] == t[j-1]) { result += s[i-1]; i--; j--; }
        else if (dp[i-1][j] > dp[i][j-1]) i--;
        else j--;
    }
    reverse(result.begin(), result.end());
    return result;
}

// Longest Common Substring — O(n * m)
int lcsSubstring(string& s, string& t) {
    int n = s.size(), m = t.size(), result = 0;
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (s[i-1] == t[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                result = max(result, dp[i][j]);
            }
        }
    return result;
}

void solve() {
    string s = "abcde", t = "ace";
    cout << "LCS length: " << lcs_length(s, t) << endl;  // 3
    cout << "LCS string: " << lcs_with_recovery(s, t) << endl;  // "ace"
    cout << "Longest common substring: " << lcsSubstring(s, t) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
