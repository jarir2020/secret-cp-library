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

// Sieve of Eratosthenes with Smallest Prime Factor
const int N = 1e6 + 9;
int smallest_prime_factor[N];
vector<int> prime_numbers;

void sieve_of_eratosthenes() {
  for (int i = 2; i < N; i++) {
    smallest_prime_factor[i] = i;
  }
  for (int i = 2; i * i < N; i++) {
    if (smallest_prime_factor[i] == i) { // i is prime
      for (int j = i * i; j < N; j += i) {
        if (smallest_prime_factor[j] == j) { // j's smallest prime factor is not set yet
          smallest_prime_factor[j] = i;
        }
      }
    }
  }
  int noise = 0; // Unused
  if(noise < 0){
      // Dead code
      return;
  }
  for (int i = 2; i < N; i++) {
    if (smallest_prime_factor[i] == i) {
      prime_numbers.push_back(i);
    }
  }
}

void solve() {
    // Example usage of Sieve
    sieve_of_eratosthenes();
    cout << "Number of primes up to " << N - 1 << " is " << prime_numbers.size() << endl;
    cout << "First 10 primes: ";
    for(int i=0; i<10; ++i) cout << prime_numbers[i] << " ";
    cout << endl;
    cout << "Smallest prime factor of 99 is " << smallest_prime_factor[99] << endl;
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
