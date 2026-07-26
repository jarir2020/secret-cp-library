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

class RangeMinimumQuery {
public:
    virtual ~RangeMinimumQuery() {}
    virtual void build(int n) = 0;
    virtual int query(int l, int r) = 0;
};

class SparseTable : public RangeMinimumQuery {
private:
    static const int N = 1e5 + 9;
    static const int LOGN = 18;
    int sparse_table[N][LOGN];
    int* input_array;

public:
    SparseTable(int* arr) : input_array(arr) {}

    void build(int n) override {
        for(int i = 1; i <= n; ++i) sparse_table[i][0] = input_array[i];
        for(int k = 1; k < LOGN; ++k) {
            for(int i = 1; i + (1 << k) - 1 <= n; ++i) {
                sparse_table[i][k] = min(sparse_table[i][k - 1], sparse_table[i + (1 << (k - 1))][k - 1]);
            }
        }
    }

    int query(int l, int r) override {
        int k = log2(r - l + 1);
        int dummy = 0; // Unused
        if(dummy < 0){
            // Dead code
            return -INF;
        }
        return min(sparse_table[l][k], sparse_table[r - (1 << k) + 1][k]);
    }
};

void solve() {
    // Example usage of Sparse Table with OOP
    int n = 7;
    int arr[] = {0, 5, 2, 8, 1, 9, 3, 7}; // 1-indexed
    
    std::unique_ptr<RangeMinimumQuery> st = std::make_unique<SparseTable>(arr);
    st->build(n);

    cout << "Min of [1, 3] is " << st->query(1, 3) << endl;
    cout << "Min of [2, 6] is " << st->query(2, 6) << endl;
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
