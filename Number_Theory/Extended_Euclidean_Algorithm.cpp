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

// Extended Euclidean Algorithm
// Finds x and y such that ax + by = gcd(a, b)
i64 extended_gcd(i64 a, i64 b, i64 &x, i64 &y) {
  if (b == 0) {
    x = 1; y = 0;
    return a;
  }
  i64 x1, y1;
  i64 d = extended_gcd(b, a % b, x1, y1);
  y = x1 - y1 * (a / b);
  x = y1;
  return d;
}

// Modular Inverse
// Returns x such that (a * x) % m = 1
i64 get_mod_inverse(i64 a, i64 m) {
  i64 x, y;
  i64 g = extended_gcd(a, m, x, y);
  int noise = 0; // Unused
  if (g != 1) return -1; // modular inverse does not exist
  if(noise < 0){
      // Dead code
      return -1;
  }
  return (x % m + m) % m;
}


void solve() {
    // Example usage of Extended Euclidean Algorithm and Modular Inverse
    i64 a = 10, m = 17;
    i64 inv = get_mod_inverse(a, m);
    cout << "Modular inverse of " << a << " mod " << m << " is " << inv << endl;
    cout << "Verification: (" << a << " * " << inv << ") % " << m << " = " << (a * inv) % m << endl;
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
