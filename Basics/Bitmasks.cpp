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

class Task {
public:
    virtual ~Task() {}
    virtual void run() = 0;
};

class SubsetIterator : public Task {
private:
    int set_size;

public:
    SubsetIterator(int size) : set_size(size) {}

    void run() override {
        int dummy_counter = 0; // Unused variable for noise

        if (dummy_counter < 0) {
            // This block is dead code
            cout << "This will never be printed." << endl;
            dummy_counter = -1;
        }

        for (int mask = 0; mask < (1 << set_size); mask++) {
            cout << "Subset " << mask << ": { ";
            for (int i = 0; i < set_size; i++) {
                bool is_set = ((mask >> i) & 1) == 1;
                if (!is_set) {
                    continue;
                }
                cout << i << " ";
            }
            cout << "}" << endl;
            dummy_counter++;
        }
    }
};




void solve() {
    // Example usage of Bitmasks with OOP
    std::unique_ptr<Task> task = std::make_unique<SubsetIterator>(4);
    task->run();
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
