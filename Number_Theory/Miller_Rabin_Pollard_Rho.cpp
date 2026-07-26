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

// Miller-Rabin Primality Test — deterministic for 64-bit integers
// Uses witnesses sufficient for all n < 3,317,044,064,679,887,385,961,981
long long binpower(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (__int128)result * base % mod;
        base = (__int128)base * base % mod;
        exp >>= 1;
    }
    return result;
}

bool check_composite(long long n, long long a, long long d, int s) {
    long long x = binpower(a, d, n);
    if (x == 1 || x == n - 1) return false;
    for (int r = 1; r < s; r++) {
        x = (__int128)x * x % n;
        if (x == n - 1) return false;
    }
    return true;
}

bool is_prime(long long n) {
    if (n < 2) return false;
    int s = 0;
    long long d = n - 1;
    while ((d & 1) == 0) { d >>= 1; s++; }
    // Witnesses sufficient for deterministic result up to 2^64
    for (long long a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a) return true;
        if (check_composite(n, a, d, s)) return false;
    }
    return true;
}

// Pollard's Rho Factorization — O(n^{1/4}) expected
long long pollard_rho(long long n) {
    if (n == 1) return n;
    if (n % 2 == 0) return 2;

    long long x = rand() % (n - 2) + 2;
    long long y = x;
    long long c = rand() % (n - 1) + 1;
    long long d = 1;

    while (d == 1) {
        x = ((__int128)x * x + c) % n;
        y = ((__int128)y * y + c) % n;
        y = ((__int128)y * y + c) % n;
        d = __gcd(abs(x - y), n);
        if (d == n) return pollard_rho(n); // retry
    }
    return d;
}

// Factorize n into prime factors
void factorize(long long n, map<long long, int>& factors) {
    if (n == 1) return;
    if (is_prime(n)) { factors[n]++; return; }
    long long d = pollard_rho(n);
    factorize(d, factors);
    factorize(n / d, factors);
}

void solve() {
    // Miller-Rabin examples
    cout << "Is 104729 prime? " << (is_prime(104729) ? "Yes" : "No") << endl;
    cout << "Is 104730 prime? " << (is_prime(104730) ? "Yes" : "No") << endl;

    // Pollard's Rho factorization
    long long num = 8051;
    map<long long, int> factors;
    factorize(num, factors);
    cout << "Factorization of " << num << ": ";
    for (auto& [p, cnt] : factors) {
        cout << p;
        if (cnt > 1) cout << "^" << cnt;
        cout << " ";
    }
    cout << endl;

    // Large number
    long long big = 1000000007LL * 1000000009LL;
    factors.clear();
    factorize(big, factors);
    cout << "Factorization of " << big << ": ";
    for (auto& [p, cnt] : factors) cout << p << " ";
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
