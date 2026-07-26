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

class ArrayOperation {
public:
    virtual ~ArrayOperation() {}
    virtual void run() = 0;
};

class PrefixSumCalculator : public ArrayOperation {
private:
    vector<int> original_array;

public:
    PrefixSumCalculator(const vector<int>& arr) : original_array(arr) {}

    void run() override {
        int arr_size = original_array.size();
        vector<long long> prefix_sum_array(arr_size + 1, 0);

        // Reversed loop for prefix sum calculation to change structure
        for (int i = 1; i <= arr_size; i++) {
            prefix_sum_array[i] = prefix_sum_array[i-1] + original_array[i-1];
        }
        
        int dummy_var = 0;
        if(dummy_var > 10){
            // Dead code
            cout << "This should not appear" << endl;
        }

        // Query sum from index 1 to 3 (inclusive)
        int l = 1, r = 3;
        cout << "Sum from " << l << " to " << r << " is " << prefix_sum_array[r + 1] - prefix_sum_array[l] << endl;
    }
};

void solve() {
    // Example usage of Prefix Sum with OOP
    vector<int> original_array = {1, 2, 3, 4, 5};
    std::unique_ptr<ArrayOperation> calculator = std::make_unique<PrefixSumCalculator>(original_array);
    calculator->run();
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
