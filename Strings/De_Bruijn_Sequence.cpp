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

// De Bruijn Sequence — O(k^n)
// Creates a cyclic string of length k^n containing every length-n string over alphabet [0, k-1]
// Useful for: brute force over all bitstrings, generating all substrings
const int MAXN = 1 << 22;
int db_result[MAXN], db_aux[MAXN];
int db_sz;

void de_bruijn(int k, int n) {
    db_sz = 0;
    if (k == 1) { db_result[0] = 0; db_sz = 1; return; }
    for (int i = 0; i < k * n; i++) db_aux[i] = 0;

    function<void(int, int)> db = [&](int t, int p) {
        if (t > n) {
            if (n % p == 0)
                for (int i = 1; i <= p; i++)
                    db_result[db_sz++] = db_aux[i];
        } else {
            db_aux[t] = db_aux[t - p];
            db(t + 1, p);
            for (int i = db_aux[t - p] + 1; i < k; i++) {
                db_aux[t] = i;
                db(t + 1, t);
            }
        }
    };
    db(1, 1);
}

void solve() {
    // Generate all 3-bit binary strings as substrings
    de_bruijn(2, 3);
    cout << "De Bruijn sequence (k=2, n=3): ";
    for (int i = 0; i < db_sz; i++) cout << db_result[i];
    cout << endl; // 00010111
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
