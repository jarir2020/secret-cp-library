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

// Josephus Problem — n people in circle, every k-th dies
// Returns the m-th killed person (1-indexed)

// O(n) version — for small n
int josephus_linear(int n, int k, int m) {
    int i;
    for (m = n - m, i = m + 1; i <= n; i++) {
        m += k;
        if (m >= i) m %= i;
    }
    return m + 1;
}

// O(k * log(n)) version — for large n
long long josephus_fast(long long n, long long k, long long m) {
    m = n - m;
    if (k <= 1) return n - m;
    long long i = m;
    while (i < n) {
        long long r = (i - m + k - 2) / (k - 1);
        if ((i + r) > n) r = n - i;
        else if (!r) r = 1;
        i += r;
        m = (m + (r * k)) % i;
    }
    return m + 1;
}

// Classic Josephus: who survives? (k=2 has O(1) solution: 2*(n - 2^floor(log2(n))) + 1)
int josephus_k2(int n) {
    int msb = 31 - __builtin_clz(n); // floor(log2(n))
    return 2 * (n - (1 << msb)) + 1;
}

void solve() {
    cout << "Josephus(10, 3, 5) = " << josephus_linear(10, 3, 5) << endl;
    cout << "Josephus fast(10, 3, 5) = " << josephus_fast(10, 3, 5) << endl;
    cout << "Josephus k=2, n=41: " << josephus_k2(41) << endl;  // 19

    // Verify both versions match
    for (int n = 1; n <= 50; n++)
        for (int k = 1; k <= 10; k++)
            for (int m = 1; m <= n; m++)
                assert(josephus_linear(n, k, m) == josephus_fast(n, k, m));
    cout << "All assertions passed!" << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
