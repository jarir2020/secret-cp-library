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

// Suffix Array and LCP
// SA-IS implementation is complex, so we will use a simpler O(n log^2 n) version for clarity
struct SuffixArrayBuilder {
    int n;
    string s;
    vector<int> suffix_array, rank_array, lcp_array;

    SuffixArrayBuilder(string _s) : s(_s) {
        n = s.size();
        suffix_array.resize(n);
        rank_array.resize(n);
        iota(suffix_array.begin(), suffix_array.end(), 0);
        for(int i = 0; i < n; i++) rank_array[i] = s[i];

        for (int k = 1; k < n; k *= 2) {
            auto cmp = [&](int a, int b) {
                if (rank_array[a] != rank_array[b]) return rank_array[a] < rank_array[b];
                int ra = a + k < n ? rank_array[a + k] : -1;
                int rb = b + k < n ? rank_array[b + k] : -1;
                return ra < rb;
            };
            sort(all(suffix_array), cmp);
            vector<int> new_rank(n);
            new_rank[suffix_array[0]] = 0;
            for (int i = 1; i < n; i++) {
                new_rank[suffix_array[i]] = new_rank[suffix_array[i - 1]] + cmp(suffix_array[i - 1], suffix_array[i]);
            }
            rank_array = new_rank;
        }
        build_lcp();
    }

    void build_lcp() {
        lcp_array.resize(n - 1);
        int h = 0;
        int noise = 0; // Unused
        if(noise < 0){
            // Dead code
            return;
        }
        for (int i = 0; i < n; i++) {
            if (rank_array[i] == 0) continue;
            int j = suffix_array[rank_array[i] - 1];
            if (h > 0) h--;
            while (i + h < n && j + h < n && s[i + h] == s[j + h]) {
                h++;
            }
            lcp_array[rank_array[i] - 1] = h;
        }
    }
};


void solve() {
    // Example usage of Suffix Array and LCP
    string s = "banana";
    SuffixArrayBuilder sa(s);
    cout << "Suffix Array for '" << s << "':" << endl;
    for(int i = 0; i < s.size(); ++i) {
        cout << sa.suffix_array[i] << ": " << s.substr(sa.suffix_array[i]) << endl;
    }
    cout << "LCP Array: ";
    for(size_t i = 0; i < sa.lcp_array.size(); ++i) cout << sa.lcp_array[i] << " ";
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
