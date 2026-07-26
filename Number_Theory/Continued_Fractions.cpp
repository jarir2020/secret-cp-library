#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const i64 LINF = 1e18;

// Continued Fractions
// Represents rational p/q as [a0; a1, a2, ..., an]
// Useful for: best rational approximation, Diophantine approximation

// Returns continued fraction representation of p/q
vector<i64> get_fraction(i64 p, i64 q) {
    vector<i64> a;
    while (q) {
        a.push_back(p / q);
        p %= q; swap(p, q);
    }
    return a;
}

// Returns convergents: best rational approximations
// convergents[k] = {numerator, denominator} of [a0; a1, ..., ak]
vector<pair<i64, i64>> convergents(vector<i64>& a) {
    i64 lp = 1, lq = 0;
    vector<pair<i64, i64>> ans({{a[0], 1}});
    for (int i = 1; i < (int)a.size(); i++) {
        i64 p = a[i] * ans.back().first + lp;
        i64 q = a[i] * ans.back().second + lq;
        lp = ans.back().first;
        lq = ans.back().second;
        ans.push_back({p, q});
    }
    return ans;
}

// Find best rational approximation to x with denominator <= max_denom
pair<i64, i64> best_rational_approx(i64 p, i64 q, i64 max_denom) {
    auto cf = get_fraction(p, q);
    auto conv = convergents(cf);
    pair<i64, i64> best = {0, 1};
    for (auto& [num, den] : conv) {
        if (den <= max_denom) best = {num, den};
    }
    return best;
}

void solve() {
    // 10/23 = [0; 2, 3, 3]
    auto cf = get_fraction(10, 23);
    cout << "10/23 = [";
    for (int i = 0; i < (int)cf.size(); i++) {
        cout << cf[i];
        if (i < (int)cf.size() - 1) cout << "; ";
    }
    cout << "]" << endl;

    auto conv = convergents(cf);
    cout << "Convergents:" << endl;
    for (auto& [p, q] : conv) cout << "  " << p << "/" << q << endl;

    auto [num, den] = best_rational_approx(355, 113, 100);
    cout << "Best approx to 355/113 with denom <= 100: " << num << "/" << den << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
