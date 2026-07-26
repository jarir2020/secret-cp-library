#ifndef CP_UTILS_H
#define CP_UTILS_H

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
#define ll long long

// Pairs and Vectors
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define read(arr) for (auto &x: arr) cin >> x;
#define print_vec(arr) for (auto arr_val: arr) { cout << arr_val << " "; } cout << endl;

// IO Macros
#define yes cout << "YES" << endl;
#define no cout << "NO" << endl;

// Constants
const int MOD = 1e9 + 7;
const int INF = 1e9;
const i64 LINF = 1e18;
const double EPS = 1e-9;

// Fun helper for "YES" responses (if you want more variety)
string yes_helper()
{
    static vector<string> yes_values = {"YES", "Yes", "yes"};
    return yes_values[rand() % yes_values.size()];
}

// Modular Exponentiation
ll mod_pow(ll a, ll b, ll m){
    ll ans = 1;
    a %= m;
    while(b){
        if (b&1) ans = (ans*a) % m;
        b /= 2;
        a = (a*a) % m;
    }
    return ans;
}

// Random Number Generator
long long rng() {
    static std::mt19937 gen(
    std::chrono::steady_clock::now().time_since_epoch().count());
    return std::uniform_int_distribution<long long>(0, INT64_MAX)(gen);
}

#endif // CP_UTILS_H
