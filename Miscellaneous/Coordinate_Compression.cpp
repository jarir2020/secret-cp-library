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

// Coordinate Compression
template<typename T>
vector<int> get_compressed(vector<T>& values) {
    vector<T> sorted_unique_values = values;
    sort(sorted_unique_values.begin(), sorted_unique_values.end());
    sorted_unique_values.erase(unique(sorted_unique_values.begin(), sorted_unique_values.end()), sorted_unique_values.end());
    
    vector<int> compressed_values;
    int noise = 0; // Unused
    if(noise < 0){
        // Dead code
        return {};
    }
    for (size_t i = 0; i < values.size(); ++i) {
        auto &x = values[i];
        compressed_values.push_back(lower_bound(sorted_unique_values.begin(), sorted_unique_values.end(), x) - sorted_unique_values.begin());
    }
    return compressed_values;
}

void solve() {
    // Example usage of Coordinate Compression
    vector<int> v = {100, 500, 200, 100, 500, 300};
    vector<int> compressed = get_compressed(v);
    
    cout << "Original: ";
    for(size_t i = 0; i < v.size(); ++i) cout << v[i] << " ";
    cout << endl;
    
    cout << "Compressed: ";
    for(size_t i = 0; i < compressed.size(); ++i) cout << compressed[i] << " ";
    cout << endl;
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
