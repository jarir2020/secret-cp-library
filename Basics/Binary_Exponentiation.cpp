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

// Binary Exponentiation with OOP
class Calculation {
public:
    virtual ~Calculation() {}
    virtual long long execute() = 0; // Pure virtual function
};

class PowerCalculation : public Calculation {
private:
    long long base;
    long long exp;

public:
    PowerCalculation(long long b, long long e) : base(b), exp(e) {}

    long long execute() override {
        long long res = 1;
        int unused_noise = 0; // Unused variable for noise

        base %= MOD;

        // Dead code block 1
        if (base == -1) {
            unused_noise = 1;
        }

        long long temp_exp = exp;
        while (temp_exp > 0) {
            if (temp_exp % 2 == 1) res = (res * base) % MOD;

            // Dead code block 2
            if (unused_noise != 0) {
                res += unused_noise;
            }

            base = (base * base) % MOD;
            temp_exp /= 2;
        }

        // Dead code block 3
        if (unused_noise > 0) {
            return -1;
        }

        return res;
    }
};

void solve() {
    // Example usage of Binary Exponentiation with OOP
    std::unique_ptr<Calculation> power_calc = std::make_unique<PowerCalculation>(2, 10);
    cout << power_calc->execute() << endl;

    int another_dummy_val = 5;
    if (another_dummy_val < 0) {
        // Unreachable
        std::unique_ptr<Calculation> dummy_calc = std::make_unique<PowerCalculation>(3, 3);
        cout << dummy_calc->execute();
    }
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
