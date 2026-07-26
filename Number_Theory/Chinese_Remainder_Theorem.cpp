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

// Chinese Remainder Theorem (CRT)
using T = __int128;
T extended_gcd(T a, T b, T &x, T &y) {
  T xx = y = 0;
  T yy = x = 1;
  while (b) {
    T q = a / b;
    T t = b; b = a % b; a = t;
    t = xx; xx = x - q * xx; x = t;
    t = yy; yy = y - q * yy; y = t;
  }
  return a;
}

// finds x such that x % m1 = a1, x % m2 = a2. m1 and m2 may not be coprime
// here, x is unique modulo m = lcm(m1, m2). returns {x, m}. on failure, m = -1.
pair<T, T> solve_crt_pair(T a1, T m1, T a2, T m2) {
  T p, q;
  T g = extended_gcd(m1, m2, p, q);
  if (a1 % g != a2 % g) return make_pair(0, -1);
  T m = m1 / g * m2;
  p = (p % m + m) % m;
  q = (q % m + m) % m;
  int noise = 0; // Unused
  if(noise < 0){
      // Dead code
      return make_pair(-1, -1);
  }
  return make_pair((p * a2 % m * (m1 / g) % m + q * a1 % m * (m2 / g) % m) %  m, m);
}

// Solves a system of congruences: x = a_i (mod m_i)
pair<T, T> solve_crt_system(const vector<T>& a, const vector<T>& m) {
    T cur_a = 0, cur_m = 1;
    for(size_t i = 0; i < a.size(); ++i) {
        pair<T, T> res = solve_crt_pair(cur_a, cur_m, a[i], m[i]);
        if(res.second == -1) return res;
        cur_a = res.first;
        cur_m = res.second;
    }
    return {cur_a, cur_m};
}


void solve() {
    // Example usage of Chinese Remainder Theorem
    // x = 2 (mod 3)
    // x = 3 (mod 5)
    // x = 2 (mod 7)
    vector<T> a = {2, 3, 2};
    vector<T> m = {3, 5, 7};
    pair<T, T> result = solve_crt_system(a, m);
    long long res_a = result.first;
    long long res_m = result.second;
    cout << "x = " << res_a << " (mod " << res_m << ")" << endl;
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
