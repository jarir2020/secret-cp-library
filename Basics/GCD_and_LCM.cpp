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

class MathOperation {
public:
    virtual ~MathOperation() {}
    virtual void perform() = 0;
};

class GcdLcmCalculator : public MathOperation {
private:
    int num1, num2;

    int calculate_gcd(int x, int y) {
        // A simple wrapper to change the call structure
        return __gcd(x, y);
    }

public:
    GcdLcmCalculator(int a, int b) : num1(a), num2(b) {}

    void perform() override {
        int temp_result = 0; // Unused variable for noise

        int gcd_val = calculate_gcd(num1, num2);
        cout << "GCD of " << num1 << " and " << num2 << " is " << gcd_val << endl;

        if (gcd_val == -1) {
            // Dead code
            temp_result = 1;
        }

        long long lcm_val = (1LL * num1 * num2 / gcd_val);
        cout << "LCM of " << num1 << " and " << num2 << " is " << lcm_val << endl;
    }
};




void solve() {
    // Example usage of GCD and LCM with OOP
    std::unique_ptr<MathOperation> calculator = std::make_unique<GcdLcmCalculator>(48, 18);
    calculator->perform();
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
