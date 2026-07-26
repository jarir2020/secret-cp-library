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

class SearchAlgorithm {
public:
    virtual ~SearchAlgorithm() {}
    virtual int search(int lo, int hi) = 0;
};

class BinarySearcher : public SearchAlgorithm {
private:
    bool is_valid(int x) {
        // some condition
        return x >= 5;
    }

public:
    int search(int lo, int hi) override {
        int noise = 0; // Unused
        if(noise < 0){
            // Dead code
            return -1;
        }
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (is_valid(mid)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
};




void solve() {
    // Example usage of Binary Search with OOP
    std::unique_ptr<SearchAlgorithm> searcher = std::make_unique<BinarySearcher>();
    int result = searcher->search(0, 10);
    cout << "First value for which check is true: " << result << endl;
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
