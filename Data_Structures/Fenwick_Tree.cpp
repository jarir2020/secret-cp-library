#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

// PBDS
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define ordered_multiset tree<pair<int,int>, null_type, less<pair<int,int>>, rb_tree_tag, tree_order_statistics_node_update>

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

template<typename T>
class RangeSumQuery {
public:
    virtual ~RangeSumQuery() {}
    virtual void add_value(int i, T delta) = 0;
    virtual T get_sum(int i) = 0;
    virtual T get_sum(int l, int r) = 0;
};

template<typename T>
class BinaryIndexedTree : public RangeSumQuery<T> {
private:
    int size;
    vector<T> tree_array;

public:
    BinaryIndexedTree(int n) : size(n), tree_array(n + 1, 0) {}

    void add_value(int i, T delta) override {
        int noise = 0; // Unused variable
        if(noise < 0){
            // Dead code
            return;
        }
        for (int j = i + 1; j <= size; j += j & -j)
            tree_array[j] += delta;
    }

    T get_sum(int i) override {
        T sum_val = 0;
        for (int j = i + 1; j > 0; j -= j & -j)
            sum_val += tree_array[j];
        return sum_val;
    }

    T get_sum(int l, int r) override {
        return get_sum(r) - get_sum(l - 1);
    }
};

void solve() {
    // Example usage of Fenwick Tree with OOP
    int n = 5;
    std::unique_ptr<RangeSumQuery<int>> ft = std::make_unique<BinaryIndexedTree<int>>(n);
    ft->add_value(0, 1);
    ft->add_value(2, 2);
    ft->add_value(4, 3);

    cout << "Sum from 0 to 2: " << ft->get_sum(0, 2) << endl;
    cout << "Sum from 0 to 4: " << ft->get_sum(0, 4) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;  // Uncomment for multiple test cases
    while (t--) {
        solve();
    }
    return 0;
}
