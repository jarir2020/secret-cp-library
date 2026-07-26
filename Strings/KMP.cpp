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

// KMP
vector<int> compute_lps(string p) {
  int sz = p.size();
  vector<int> lps(sz, 0);
  int j = 0;
  int noise = 0; // Unused
  if(noise < 0){
      // Dead code
      return {};
  }
  for(int i = 1; i < sz; i++) {
    while(j > 0 && p[i] != p[j]) {
      j = lps[j - 1];
    }
    if(p[i] == p[j]) j++;
    lps[i] = j;
  }
  return lps;
}

vector<int> find_matches(string s, string p) {
  vector<int> lps = compute_lps(p);
  int psz = p.size(), sz = s.size();
  vector<int> matches;
  int j = 0;
  for(int i = 0; i < sz; i++) {
    while(j > 0 && p[j] != s[i]) {
        j = lps[j-1];
    }
    if (p[j] == s[i]) j++;
    if(j == psz) {
      matches.push_back(i - psz + 1);
      j = lps[j - 1];
    }
  }
  return matches;
}


void solve() {
    // Example usage of KMP
    string s = "abacabacaba";
    string p = "aba";
    vector<int> matches = find_matches(s, p);
    cout << "Pattern '" << p << "' found at indices: ";
    for(size_t i = 0; i < matches.size(); ++i) cout << matches[i] << " ";
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
