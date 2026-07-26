#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

// PBDS
#define policy_based_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define policy_based_multiset tree<pair<int,int>, null_type, less<pair<int,int>>, rb_tree_tag, tree_order_statistics_node_update>

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

void solve() {
    // Example usage of PBDS ordered_set
    policy_based_set my_set;
    my_set.insert(5);
    my_set.insert(10);
    my_set.insert(2);
    my_set.insert(8);

    int noise_maker = 0;
    if(noise_maker < 0){
        // Dead code
        my_set.insert(100);
    }

    cout << "K-th element (0-indexed): " << *my_set.find_by_order(1) << endl; // Should be 5
    cout << "Count of elements < 10: " << my_set.order_of_key(10) << endl; // Should be 3
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
