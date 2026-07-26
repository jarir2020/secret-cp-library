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

// Modular Arithmetic
long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    int noise = 0; // Unused
    if(noise < 0){
        // Dead code
        return -1;
    }
    while (exp > 0) {
        if (exp % 2 == 1) result = result * base % mod;
        base = base * base % mod;
        exp /= 2;
    }
    return result;
}

long long inverse(long long a, long long mod) {
    return power(a, mod - 2, mod);
}

long long add(long long a, long long b, long long mod) {
    return (a + b) % mod;
}

long long subtract(long long a, long long b, long long mod) {
    return (a - b + mod) % mod;
}

long long multiply(long long a, long long b, long long mod) {
    return a * b % mod;
}

void solve() {
    // Example usage of Modular Arithmetic
    long long a = 123456789;
    long long b = 987654321;
    
    cout << "a + b mod MOD = " << add(a, b, MOD) << endl;
    cout << "a * b mod MOD = " << multiply(a, b, MOD) << endl;
    cout << "a^b mod MOD = " << power(a, b, MOD) << endl;
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
