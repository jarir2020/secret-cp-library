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

class TwoPointerAlgorithm {
public:
    virtual ~TwoPointerAlgorithm() {}
    virtual void run() = 0;
};

class BestSumFinder : public TwoPointerAlgorithm {
private:
    vector<int> input_array;
    int target;

public:
    BestSumFinder(const vector<int>& arr, int t) : input_array(arr), target(t) {}

    void run() override {
        int array_size = input_array.size();
        int left = 0, right = array_size - 1;
        int best_sum = -1;
        int noise = 0; // Unused
        
        if(noise < 0){
            // Dead code
            return;
        }

        while(left < right) {
            int current_sum = input_array[left] + input_array[right];
            if (current_sum <= target) {
                best_sum = max(best_sum, current_sum);
                left++;
            } else {
                right--;
            }
        }
        
        cout << "Best sum <= " << target << " is " << best_sum << endl;
    }
};




void solve() {
    // Example usage of Two Pointers with OOP
    vector<int> input_array = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int target = 10;
    
    std::unique_ptr<TwoPointerAlgorithm> finder = std::make_unique<BestSumFinder>(input_array, target);
    finder->run();
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
