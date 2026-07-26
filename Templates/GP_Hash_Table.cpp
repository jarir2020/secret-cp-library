#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const i64 LINF = 1e18;

// GP Hash Table — anti-hack hash map
// Usage: gp_hash_table<int, int> mp;
// Faster than unordered_map, resistant to hash DoS attacks
// Or use custom_hash with unordered_map for standard library approach

// Option 1: gp_hash_table (fastest, GCC extension)
// gp_hash_table<int, int> mp;

// Option 2: custom_hash for unordered_map
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x = x + 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

void solve() {
    // gp_hash_table usage
    gp_hash_table<int, int> ght;
    ght[1] = 10; ght[2] = 20; ght[3] = 30;
    cout << "gp_hash_table[2] = " << ght[2] << endl;

    // custom_hash usage
    unordered_map<int, int, custom_hash> safe_map;
    safe_map[1] = 100; safe_map[2] = 200;
    cout << "custom_hash map[1] = " << safe_map[1] << endl;

    // Safe for competitive programming (anti-hack)
    unordered_set<int, custom_hash> safe_set;
    safe_set.insert(42);
    cout << "Contains 42? " << safe_set.count(42) << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
