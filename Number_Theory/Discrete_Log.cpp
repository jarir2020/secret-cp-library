#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const i64 LINF = 1e18;

// Baby-step Giant-step — O(sqrt(m))
// Find minimum x such that a^x ≡ b (mod m), where gcd(a, m) = 1
// Returns -1 if no solution
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

int discrete_log(int a, int b, int m) {
    a %= m; b %= m;
    int n = (int)sqrt(m + 0.0) + 1;
    long long pw = 1;
    for (int i = 0; i < n; i++) pw = pw * a % m;

    gp_hash_table<long long, int> vals;
    long long cur = pw;
    for (int p = 1; p <= n; p++) {
        if (!vals[cur]) vals[cur] = p;
        cur = cur * pw % m;
    }

    int ans = INF;
    cur = b;
    for (int q = 0; q <= n; q++) {
        if (vals.find(cur) != vals.end()) {
            long long nw = (long long)vals[cur] * n - q;
            if (nw < ans) ans = nw;
        }
        cur = cur * a % m;
    }
    return ans == INF ? -1 : ans;
}

// Non-coprime version: handles gcd(a, m) != 1
i64 extended_euclid(i64 a, i64 b, i64& x, i64& y) {
    if (b == 0) { x = 1; y = 0; return a; }
    i64 x1, y1;
    i64 d = extended_euclid(b, a % b, x1, y1);
    x = y1; y = x1 - y1 * (a / b);
    return d;
}

i64 inverse(i64 a, i64 m) {
    i64 x, y;
    i64 g = extended_euclid(a, m, x, y);
    if (g != 1) return -1;
    return (x % m + m) % m;
}

int discrete_log_noncoprime(int a, int b, int m) {
    if (m == 1) return 0;
    if (b == 1) return 0;
    if (__gcd(a, m) == 1) return discrete_log(a, b, m);
    int g = __gcd(a, m);
    if (b % g != 0) return -1;
    int p = inverse(a / g, m / g);
    int nw = discrete_log_noncoprime(a, 1LL * b / g * p % (m / g), m / g);
    if (nw == -1) return -1;
    return nw + 1;
}

void solve() {
    cout << "3^x ≡ 4 (mod 7): x = " << discrete_log(3, 4, 7) << endl;
    cout << "2^x ≡ 3 (mod 5): x = " << discrete_log(2, 3, 5) << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
