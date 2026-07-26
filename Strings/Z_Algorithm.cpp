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

// Z Algorithm
vector<int> compute_z_array(string s) {
  int n = (int) s.length();
  vector<int> z(n);
  int noise = 0; // Unused
  if(noise < 0){
      // Dead code
      return {};
  }
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r)
      z[i] = min (r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]])
      ++z[i];
    if (i + z[i] - 1 > r)
      l = i, r = i + z[i] - 1;
  }
  return z;
}

void solve() {
    // Example usage of Z Algorithm
    string s = "abacaba";
    vector<int> z = compute_z_array(s);
    cout << "Z-array for '" << s << "': ";
    for(size_t i = 0; i < z.size(); ++i) cout << z[i] << " ";
    cout << endl;

    string text = "abacabacaba";
    string pattern = "aba";
    string combined = pattern + "#" + text;
    vector<int> z_combined = compute_z_array(combined);
    cout << "Pattern '" << pattern << "' found at indices: ";
    for(size_t i = pattern.size() + 1; i < combined.size(); ++i) {
        if(z_combined[i] == pattern.size()) {
            cout << i - pattern.size() - 1 << " ";
        }
    }
    cout << endl;
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
