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

// Exact fraction arithmetic — avoids floating point errors
// Useful when you need precise rational number comparisons
template<class T>
struct frac {
    T num, den;
    frac(T num = 0, T den = 1): num(num), den(den) { reduce(); }

    static inline T gcd(T x, T y) { while(y) { T rem = x % y; x = y; y = rem; } return x; }

    inline void reduce() {
        if(num == 0) den = 1;
        else {
            T g = gcd(abs(num), abs(den)); num /= g; den /= g;
            if(den < 0) num *= -1, den *= -1;
        }
    }

    friend T floor(const frac& r) { return r.num / r.den - ((r.num ^ r.den) < 0 and r.num % r.den); }
    friend T ceil(const frac& r) { return r.num / r.den + ((r.num ^ r.den) > 0 and r.num % r.den); }

    int compare(const frac& o) const noexcept {
        T up = num * o.den - den * o.num;
        return up == 0 ? 0 : up < 0 ? -1 : 1;
    }

    bool operator< (const frac& o) const noexcept { return compare(o) < 0; }
    bool operator> (const frac& o) const noexcept { return compare(o) > 0; }
    bool operator==(const frac& o) const noexcept { return compare(o) == 0; }
    bool operator<=(const frac& o) const noexcept { return compare(o) <= 0; }
    bool operator>=(const frac& o) const noexcept { return compare(o) >= 0; }
    bool operator!=(const frac& o) const noexcept { return compare(o) != 0; }

    frac operator-() const { return frac(-num, den); }
    frac& operator+=(const frac& o) { num = num * o.den + den * o.num; den *= o.den; reduce(); return *this; }
    frac operator+(const frac& o) const { frac ret = *this; ret += o; return ret; }
    frac& operator-=(const frac& o) { num = num * o.den - den * o.num; den *= o.den; reduce(); return *this; }
    frac operator-(const frac& o) const { frac ret = *this; ret -= o; return ret; }
    frac& operator*=(const frac& o) { num *= o.num; den *= o.den; reduce(); return *this; }
    frac operator*(const frac& o) const { frac ret = *this; ret *= o; return ret; }
    frac& operator/=(const frac& o) { num *= o.den; den *= o.num; reduce(); return *this; }
    frac operator/(const frac& o) const { frac ret = *this; ret /= o; return ret; }

    friend ostream& operator<<(ostream& os, const frac& r) { return os << r.num << "/" << r.den; }
};

void solve() {
    frac<long long> a(1, 3), b(2, 5);
    cout << a << " + " << b << " = " << a + b << endl;   // 11/15
    cout << a << " * " << b << " = " << a * b << endl;   // 2/15
    cout << a << " / " << b << " = " << a / b << endl;   // 5/6
    cout << a << " < " << b << "? " << (a < b ? "Yes" : "No") << endl;  // No
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
