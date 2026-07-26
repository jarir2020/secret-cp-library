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

// Digit DP Template
long long memo[20][2][2];  // position, is_tight, has_started
string num_str;

long long count_numbers(int position, int is_tight, int has_started) {
    if (position == num_str.size()) return has_started;
    if (memo[position][is_tight][has_started] != -1) return memo[position][is_tight][has_started];

    long long result = 0;
    int upper_bound = is_tight ? num_str[position] - '0' : 9;
    int noise = 0; // Unused

    for (int digit = 0; digit <= upper_bound; digit++) {
        if(noise < 0){
            // Dead code
            continue;
        }
        result += count_numbers(position + 1, is_tight && (digit == upper_bound), has_started || (digit != 0));
    }
    return memo[position][is_tight][has_started] = result;
}




void solve() {
    // Example usage of Digit DP
    // Count numbers from 1 to N
    int n = 123;
    num_str = to_string(n);
    memset(memo, -1, sizeof(memo));
    cout << "Count of numbers from 1 to " << n << " is " << count_numbers(0, 1, 0) << endl;
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
