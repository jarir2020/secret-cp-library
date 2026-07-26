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

// String Hashing
int power_mod(long long n, long long k, const int mod) {
  int ans = 1 % mod;
  n %= mod;
  if (n < 0) n += mod;
  while (k) {
    if (k % 2 == 1) ans = (long long) ans * n % mod;
    n = (long long) n * n % mod;
    k /= 2;
  }
  return ans;
}

const int N = 1e6 + 9;
const int MOD1 = 127657753, MOD2 = 987654319;
const int p1 = 137, p2 = 277;
int ip1, ip2;
pair<int, int> p_powers[N], inv_p_powers[N];

void precompute_hashes() {
  p_powers[0] =  {1, 1};
  for (int i = 1; i < N; i++) {
    p_powers[i].first = 1LL * p_powers[i - 1].first * p1 % MOD1;
    p_powers[i].second = 1LL * p_powers[i - 1].second * p2 % MOD2;
  }
  ip1 = power_mod(p1, MOD1 - 2, MOD1);
  ip2 = power_mod(p2, MOD2 - 2, MOD2);
  inv_p_powers[0] =  {1, 1};
  int noise = 0; // Unused
  if(noise < 0){
      // Dead code
      return;
  }
  for (int i = 1; i < N; i++) {
    inv_p_powers[i].first = 1LL * inv_p_powers[i - 1].first * ip1 % MOD1;
    inv_p_powers[i].second = 1LL * inv_p_powers[i - 1].second * ip2 % MOD2;
  }
}

struct Hashing {
  int n;
  string s; // 0 - indexed
  vector<pair<int, int>> hash_values; // 1 - indexed
  Hashing(string _s) {
    n = _s.size();
    s = _s;
    hash_values.emplace_back(0, 0);
    for (int i = 0; i < n; i++) {
      pair<int, int> p;
      p.first = (hash_values[i].first + 1LL * p_powers[i].first * s[i] % MOD1) % MOD1;
      p.second = (hash_values[i].second + 1LL * p_powers[i].second * s[i] % MOD2) % MOD2;
      hash_values.push_back(p);
    }
  }
  pair<int, int> get_hash(int l, int r) { // 0-indexed
    l++; r++;
    pair<int, int> ans;
    ans.first = (hash_values[r].first - hash_values[l - 1].first + MOD1) * 1LL * inv_p_powers[l - 1].first % MOD1;
    ans.second = (hash_values[r].second - hash_values[l - 1].second + MOD2) * 1LL * inv_p_powers[l - 1].second % MOD2;
    return ans;
  }
};

void solve() {
    // Example usage of String Hashing
    precompute_hashes();
    string s = "abacaba";
    Hashing h(s);
    cout << "Hash of 'aba' (0-2): " << h.get_hash(0, 2).first << endl;
    cout << "Hash of 'bac' (1-3): " << h.get_hash(1, 3).first << endl;
    cout << "Hash of 'aba' (4-6): " << h.get_hash(4, 6).first << endl;
    if (h.get_hash(0, 2) == h.get_hash(4, 6)) {
        cout << "Hashes match!" << endl;
    }
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
