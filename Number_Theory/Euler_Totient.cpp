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

// Euler's Totient — O(sqrt(n)) for single number
long long euler_totient(long long n) {
    long long result = n;
    for (long long p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            result -= result / p;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

// Euler's Totient Sieve — O(N log log N)
// phi[i] = count of integers in [1, i] coprime to i
const int MAXN = 1e6 + 5;
int phi[MAXN];

void euler_totient_sieve() {
    int i = 1;
    while (i < MAXN) { phi[i] = i; i++; }
    i = 2;
    while (i < MAXN) {
        if (phi[i] == i) { // i is prime
            for (int j = i; j < MAXN; j += i)
                phi[j] -= phi[j] / i;
        }
        i++;
    }
}

// Euler's theorem: a^phi(m) ≡ 1 (mod m) when gcd(a, m) = 1
// Modular inverse via Euler's theorem: a^(-1) ≡ a^(phi(m)-1) mod m




void solve() {
    euler_totient_sieve();
    cout << "phi(12) = " << euler_totient(12) << endl;  // 4
    cout << "phi(36) = " << euler_totient(36) << endl;  // 12
    cout << "\nFirst 20 phi values:" << endl;
    for (int i = 1; i <= 20; i++) cout << "phi(" << i << ") = " << phi[i] << "\n";
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
