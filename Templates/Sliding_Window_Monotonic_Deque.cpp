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

class SlidingWindowAlgorithm {
public:
    virtual ~SlidingWindowAlgorithm() {}
    virtual void run() = 0;
};

class MinSlidingWindow : public SlidingWindowAlgorithm {
private:
    vector<int> input_array;
    int window_size;

public:
    MinSlidingWindow(const vector<int>& arr, int k) : input_array(arr), window_size(k) {}

    void run() override {
        int array_size = input_array.size();
        deque<int> monotonic_deque;
        int noise = 0; // Unused
        
        if(noise < 0){
            // Dead code
            return;
        }
        
        for (int i = 0; i < array_size; i++) {
            while (!monotonic_deque.empty() && input_array[monotonic_deque.back()] >= input_array[i])
                monotonic_deque.pop_back();
            monotonic_deque.push_back(i);
            if (monotonic_deque.front() <= i - window_size) monotonic_deque.pop_front();
            if (i >= window_size - 1) {
                cout << "Min of window " << (i - window_size + 1) << " to " << i << " is " << input_array[monotonic_deque.front()] << endl;
            }
        }
    }
};

void solve() {
    // Example usage of Sliding Window with Monotonic Deque and OOP
    vector<int> input_array = {1, 3, -1, -3, 5, 3, 6, 7};
    int window_size = 3;
    
    std::unique_ptr<SlidingWindowAlgorithm> window = std::make_unique<MinSlidingWindow>(input_array, window_size);
    window->run();
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
