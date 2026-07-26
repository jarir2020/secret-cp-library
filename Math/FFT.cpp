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

// Fast Fourier Transform — O(n log n) for polynomial multiplication
// Handles complex-valued FFT
typedef complex<double> cd;
const double PI = acos(-1.0);

void fft(vector<cd>& a, bool invert) {
    int n = a.size();
    // Bit-reversal permutation
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }

    // Butterfly operations
    for (int len = 2; len <= n; len <<= 1) {
        double angle = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(angle), sin(angle));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd& x : a) x /= n;
    }
}

// Multiply two polynomials: returns coefficients of product
vector<long long> multiply(vector<long long> const& a, vector<long long> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n); fb.resize(n);

    fft(fa, false); fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);

    vector<long long> result(n);
    for (int i = 0; i < n; i++)
        result[i] = (long long)round(fa[i].real());
    return result;
}

// NTT (Number Theoretic Transform) — modular version, no floating point errors
// MOD must be of form c * 2^k + 1
const int MOD2 = 998244353; // 119 * 2^23 + 1
const int ROOT = 31;

long long mod_pow2(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

void ntt(vector<long long>& a, bool invert, int mod = MOD2) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        long long wlen = mod_pow2(ROOT, (mod - 1) / len, mod);
        if (invert) wlen = mod_pow2(wlen, mod - 2, mod);
        for (int i = 0; i < n; i += len) {
            long long w = 1;
            for (int j = 0; j < len / 2; j++) {
                long long u = a[i + j], v = a[i + j + len / 2] * w % mod;
                a[i + j] = (u + v) % mod;
                a[i + j + len / 2] = (u - v + mod) % mod;
                w = w * wlen % mod;
            }
        }
    }

    if (invert) {
        long long n_inv = mod_pow2(n, mod - 2, mod);
        for (long long& x : a) x = x * n_inv % mod;
    }
}

vector<long long> multiply_ntt(vector<long long> a, vector<long long> b) {
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    a.resize(n); b.resize(n);
    ntt(a, false); ntt(b, false);
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % MOD2;
    ntt(a, true);
    return a;
}

void solve() {
    // Polynomial multiplication: (1 + 2x + 3x^2) * (2 + x)
    vector<long long> a = {1, 2, 3};
    vector<long long> b = {2, 1};

    cout << "FFT result: ";
    auto res = multiply(a, b);
    for (int i = 0; i < (int)res.size(); i++) cout << res[i] << " ";
    cout << endl; // 2 5 8 3

    cout << "NTT result: ";
    auto res2 = multiply_ntt(a, b);
    for (int i = 0; i < (int)res2.size(); i++) cout << res2[i] << " ";
    cout << endl; // 2 5 8 3
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
