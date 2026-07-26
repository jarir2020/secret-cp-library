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
#define fbo find_by_order
#define ook order_of_key

// Type aliases
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
#define ll long long
#define ull unsigned long long
#define ld long double

// Pairs and Vectors
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vi vector<int>
#define vll vector<ll>
#define vpii vector<pii>
#define vpll vector<pll>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

// Loop macros
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define repA(i, a, n) for (int i = (a); i <= (n); ++i)
#define repD(i, a, n) for (int i = (a); i >= (n); --i)

// Sorting
#define sortA(v) sort(v.begin(), v.end())
#define sortD(v) sort(v.begin(), v.end(), greater<>())

// IO
#define read(arr) for (auto &x: arr) cin >> x;
#define print_vec(arr) for (auto arr_val: arr) { cout << arr_val << " "; } cout << endl;
#define yes cout << "YES" << endl;
#define no cout << "NO" << endl;
#define el '\n'
#define sp ' '

// Debugging macro (uncomment to enable)
// #define DEBUG(x) cerr << #x << " = " << (x) << endl

// Modular arithmetic helpers
#define _ % MOD
#define __ %= MOD

// Constants
const int MOD = 1e9 + 7;
const int INF = 1e9 + 5;
const i64 LINF = 1e18;
const double EPS = 1e-9;
const int MAXN = 1e6 + 3;

// DSU
struct DSU {
    vector<int> par, sz;
    int num_grp;
    DSU(int n) : par(n), sz(n, 1), num_grp(n) { iota(par.begin(), par.end(), 0); }
    int find(int u) { return u == par[u] ? u : par[u] = find(par[u]); }
    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (sz[u] > sz[v]) swap(u, v);
        par[u] = v; sz[v] += sz[u]; num_grp--;
    }
    int component() { return num_grp; }
    int sz_component(int u) { return sz[find(u)]; }
};

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

// Modular arithmetic
ll add(ll a, ll b) { return (a % MOD + b % MOD) % MOD; }
ll sub(ll a, ll b) { return (a % MOD - b % MOD + MOD) % MOD; }
ll mul(ll a, ll b) { return (a % MOD * (b % MOD)) % MOD; }
ll inv(ll a) { return mod_pow(a, MOD - 2, MOD); }

// Random number generator
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rdi(int l = 0, int r = 1e9) { return uniform_int_distribution<int>(l, r)(rng); }

// Solve function - put your logic here



void solve() {
    // Your code here
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
