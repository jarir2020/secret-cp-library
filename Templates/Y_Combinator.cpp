#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using namespace std;

// Type aliases
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

// Constants
const int MOD = 1e9 + 7;
const int INF = 1e9;
const i64 LINF = 1e18;
const double EPS = 1e-9;

// Y Combinator — enables recursive lambdas
// Useful when you need DFS/BFS inside a lambda without writing a separate function
template<class T> class Y {
    T f_;
public:
    template<class U> explicit Y(U&& f): f_(forward<U>(f)) {}
    template<class ...Args> decltype(auto) operator()(Args&&... args) {
        return f_(ref(*this), forward<Args>(args)...);
    }
};  template<class T> Y(T) -> Y<T>; // C++17 deduction guide

void solve() {
    // Factorial via recursive lambda
    auto factorial = Y([&](auto self, int n) -> int {
        return n == 0 ? 1 : n * self(n - 1);
    });
    cout << "5! = " << factorial(5) << endl;

    // DFS on tree without writing a separate function
    vector<vector<int>> tree = {{1, 2}, {3, 4}, {}, {}, {}};
    auto dfs = Y([&](auto self, int u, int depth) -> void {
        cout << "Node " << u << " at depth " << depth << endl;
        for (int v : tree[u]) self(v, depth + 1);
    });
    dfs(0, 0);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
