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

class Math {
public:
    virtual ~Math() {}
    virtual long long power(long long base, long long exp) = 0;
    virtual long long nCr(int n, int r) = 0;
    virtual long long gcd(long long a, long long b) = 0;
    virtual long long lcm(long long a, long long b) = 0;
};

class MathHelpers : public Math {
public:
    long long power(long long base, long long exp) override {
        long long res = 1;
        base %= MOD;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp /= 2;
        }
        return res;
    }

    long long nCr(int n, int r) override {
        if (r < 0 || r > n) return 0;
        if (r == 0 || r == n) return 1;
        if (r > n / 2) r = n - r;
        vector<long long> C(r + 1, 0);
        C[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = min(i, r); j > 0; j--)
                C[j] = (C[j] + C[j - 1]) % MOD;
        }
        return C[r];
    }

    long long gcd(long long a, long long b) override {
        return b == 0 ? a : gcd(b, a % b);
    }

    long long lcm(long long a, long long b) override {
        return (a / gcd(a, b)) * b;
    }
};

void solve() {
    // Example usage of MathHelpers
    std::unique_ptr<Math> math = std::make_unique<MathHelpers>();
    cout << "7 C 3 = " << math->nCr(7, 3) << endl;
    cout << "GCD of 48 and 18 = " << math->gcd(48, 18) << endl;
    cout << "LCM of 48 and 18 = " << math->lcm(48, 18) << endl;
    cout << "2^10 mod MOD = " << math->power(2, 10) << endl;
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
