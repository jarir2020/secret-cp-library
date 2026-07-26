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

// Modular Exponentiation
i64 mod_pow(i64 a, i64 b, i64 m){
    i64 ans = 1;
    a %= m;
    while(b){
        if (b&1) ans = (ans*a) % m;
        b /= 2;
        a = (a*a) % m;
    }
    return ans;
}

// Factorial and Inverse Factorial precomputation
// O(N) precompute, O(1) per nCr query
const int MAXN = 2e6 + 5;
long long fact[MAXN], inv_fact[MAXN];

void precompute_factorials() {
    fact[0] = 1;
    int i = 1;
    while (i < MAXN) {
        fact[i] = fact[i - 1] * i % MOD;
        i++;
    }
    inv_fact[MAXN - 1] = mod_pow(fact[MAXN - 1], MOD - 2, MOD);
    i = MAXN - 2;
    while (i >= 0) {
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
        i--;
    }
}

long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] % MOD * inv_fact[r] % MOD * inv_fact[n - r] % MOD;
}

long long nPr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] % MOD * inv_fact[n - r] % MOD;
}

void solve() {
    precompute_factorials();
    cout << "10C3 = " << nCr(10, 3) << endl;  // 120
    cout << "10P3 = " << nPr(10, 3) << endl;  // 720
    cout << "100C50 = " << nCr(100, 50) << endl;
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
