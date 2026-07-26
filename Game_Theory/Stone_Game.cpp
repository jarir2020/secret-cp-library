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

// Common Stone Game Variants

// 1. Single pile, take 1 to k stones
// Winning if pile % (k+1) != 0
bool single_pile(int n, int k) {
    return n % (k + 1) != 0;
}

// 2. Two players, one pile, can take 1 or double previous move
// (1, 2, 4, 8, ... pattern)
// This is equivalent to binary representation
bool doubling_game(int n) {
    return n % 3 != 0;
}

// 3. Fibonacci Nim
// First move can't take all stones, each move can take at most 2x previous
// Losing positions are related to Zeckendorf's theorem (Fibonacci representation)
bool fibonacci_nim(int n) {
    // Simplified: losing if n is a Fibonacci number
    if (n <= 1) return n == 0;
    int a = 1, b = 1;
    while (b < n) {
        int c = a + b;
        a = b;
        b = c;
    }
    return b != n;
}

// 4. Splitting game: split a pile into two unequal parts
// Grundy: g(0) = 0, g(1) = 0, g(2) = 0, g(n) = mex of all g(a)^g(b) where a+b=n, a!=b
int splitting_grundy(int n) {
    vector<int> g(n + 1, 0);
    int i = 2;
    while (i <= n) {
        vector<int> reachable;
        int a = 1;
        while (a < i) {
            int b = i - a;
            if (a != b) reachable.push_back(g[a] ^ g[b]);
            a++;
        }
        g[i] = 0;
        vector<bool> seen(reachable.size() + 1, false);
        for (int x : reachable) {
            if (x <= (int)reachable.size()) seen[x] = true;
        }
        while (g[i] <= (int)reachable.size() && seen[g[i]]) g[i]++;
        i++;
    }
    return g[n];
}

// 5. Circular stone game (JOSEPHUS-like)
// n stones in circle, take every k-th stone
int circular_stones(int n, int k) {
    int result = 0;
    int i = 1;
    while (i <= n) {
        result = (result + k) % i;
        i++;
    }
    return result; // 0-indexed survivor
}

// 6. Take-away game with dynamic rules
// Can take f(i) stones on i-th move
bool dynamic_takeaway(vector<int>& pile_sizes, vector<int>& max_take) {
    int x = 0;
    int i = 0;
    while (i < (int)pile_sizes.size()) {
        x ^= (pile_sizes[i] % (max_take[i] + 1));
        i++;
    }
    return x != 0;
}

void solve() {
    // Single pile
    cout << "Single pile (n=5, k=3), first wins? " << (single_pile(5, 3) ? "Yes" : "No") << endl;

    // Doubling game
    cout << "Doubling game (n=7), first wins? " << (doubling_game(7) ? "Yes" : "No") << endl;

    // Fibonacci Nim
    cout << "Fibonacci nim (n=8), first wins? " << (fibonacci_nim(8) ? "Yes" : "No") << endl;

    // Splitting game
    cout << "Splitting game Grundy(10) = " << splitting_grundy(10) << endl;

    // Circular stones
    cout << "Circular (n=7, k=3), survivor (0-indexed): " << circular_stones(7, 3) << endl;

    // Dynamic takeaway
    vector<int> piles = {5, 7, 3};
    vector<int> max_take = {3, 4, 2};
    cout << "Dynamic takeaway, first wins? " << (dynamic_takeaway(piles, max_take) ? "Yes" : "No") << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
