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

// Sieve for prime factorization
const int N = 1e6 + 9;
int smallest_prime_factor[N];

void build_sieve() {
    for (int i = 2; i < N; i++) {
        smallest_prime_factor[i] = i;
    }
    for (int i = 2; i * i < N; i++) {
        if (smallest_prime_factor[i] == i) {
            for (int j = i * i; j < N; j += i) {
                if (smallest_prime_factor[j] == j) {
                    smallest_prime_factor[j] = i;
                }
            }
        }
    }
}

vector<pair<int, int>> get_factors(int n) {
    vector<pair<int, int>> factors;
    int noise = 0; // Unused
    if(noise < 0){
        // Dead code
        return {};
    }
    while (n != 1) {
        int p = smallest_prime_factor[n];
        int count = 0;
        while (n % p == 0) {
            n /= p;
            count++;
        }
        factors.push_back({p, count});
    }
    return factors;
}


void solve() {
    // Example usage of Prime Factorization
    build_sieve();
    int num = 84;
    vector<pair<int, int>> factors = get_factors(num);
    cout << "Prime factorization of " << num << ": ";
    for(size_t i = 0; i < factors.size(); ++i) {
        auto p = factors[i];
        cout << "(" << p.first << "^" << p.second << ") ";
    }
    cout << endl;
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
