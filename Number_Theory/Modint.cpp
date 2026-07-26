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

// Modular Integer — auto-reduces after every operation
// Eliminates manual % MOD everywhere
// MOD must be prime for inv()
template <const int32_t MOD>
struct modint {
    int32_t value;
    modint() = default;
    modint(int32_t value_) : value(value_) {}
    inline modint operator+(modint o) const { int32_t c = value + o.value; return modint(c >= MOD ? c - MOD : c); }
    inline modint operator-(modint o) const { int32_t c = value - o.value; return modint(c < 0 ? c + MOD : c); }
    inline modint operator*(modint o) const { int32_t c = (int64_t)value * o.value % MOD; return modint(c); }
    inline modint& operator+=(modint o) { value += o.value; if (value >= MOD) value -= MOD; return *this; }
    inline modint& operator-=(modint o) { value -= o.value; if (value < 0) value += MOD; return *this; }
    inline modint& operator*=(modint o) { value = (int64_t)value * o.value % MOD; return *this; }
    inline modint operator-() const { return modint(value ? MOD - value : 0); }
    modint pow(uint64_t k) const { modint x = *this, y = 1; for (; k; k >>= 1) { if (k & 1) y *= x; x *= x; } return y; }
    modint inv() const { return pow(MOD - 2); }
    inline modint operator/(modint o) const { return *this * o.inv(); }
    inline modint operator/=(modint o) { return *this *= o.inv(); }
    inline bool operator==(modint o) const { return value == o.value; }
    inline bool operator!=(modint o) const { return value != o.value; }
    inline bool operator<(modint o) const { return value < o.value; }
    inline bool operator>(modint o) const { return value > o.value; }
    friend istream& operator>>(istream& in, modint& n) { return in >> n.value; }
    friend ostream& operator<<(ostream& out, modint n) { return out << n.value; }
};
template <int32_t MOD> modint<MOD> operator*(int64_t v, modint<MOD> n) { return modint<MOD>(v % MOD) * n; }
template <int32_t MOD> modint<MOD> operator*(int32_t v, modint<MOD> n) { return modint<MOD>(v) * n; }

using mint = modint<MOD>;

// Combinatorics with modint
struct Combi {
    int n;
    vector<mint> facts, finvs;
    Combi(int _n) : n(_n), facts(_n), finvs(_n) {
        facts[0] = 1;
        for (int i = 1; i < n; i++) facts[i] = facts[i-1] * i;
        finvs[n-1] = facts[n-1].inv();
        for (int i = n-2; i >= 0; i--) finvs[i] = finvs[i+1] * (i+1);
    }
    mint nCr(int n, int r) {
        if (r < 0 || r > n) return 0;
        return facts[n] * finvs[r] * finvs[n-r];
    }
};

void solve() {
    mint a = 3, b = 5;
    cout << a << " + " << b << " = " << a + b << endl;
    cout << a << " * " << b << " = " << a * b << endl;
    cout << a << " / " << b << " = " << a / b << endl;

    Combi C(20);
    cout << "10C3 = " << C.nCr(10, 3) << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
