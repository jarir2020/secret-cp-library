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

// Sprague-Grundy Theorem
// Every impartial game under normal play is equivalent to a Nim heap
// The Grundy number (nimber) determines the game state
// XOR of all Grundy numbers = 0 means losing position

// mex = Minimum Excluded value (smallest non-negative integer not in the set)
int mex(vector<int>& values) {
    int n = values.size();
    vector<bool> seen(n + 1, false);
    int i = 0;
    while (i < n) {
        if (values[i] <= n) seen[values[i]] = true;
        i++;
    }
    int result = 0;
    while (seen[result]) result++;
    return result;
}

// Grundy numbers for a game on a single pile
// Game: from pile of size n, you can move to any state in moves[]
// e.g. moves = {1, 2, 3} means you can remove 1, 2, or 3 stones
vector<int> compute_grundy_table(int max_state, vector<int>& moves) {
    vector<int> g(max_state + 1, 0);
    int n = 1;
    while (n <= max_state) {
        vector<int> reachable;
        for (int m : moves) {
            if (n - m >= 0) reachable.push_back(g[n - m]);
        }
        g[n] = mex(reachable);
        n++;
    }
    return g;
}

// Example: Wythoff's Game
// Two piles, can remove from one pile or equal amount from both
// Losing positions: (floor(k*phi), floor(k*phi^2)) for k = 0, 1, 2, ...
// where phi = (1 + sqrt(5)) / 2
bool wythoff_losing(int a, int b) {
    if (a > b) swap(a, b);
    double phi = (1.0 + sqrt(5.0)) / 2.0;
    int k = b - a;
    int expected_a = (int)(k * phi);
    return a == expected_a;
}

// Grundy numbers for subtraction game
// Can remove any amount from 1 to k
int subtraction_grundy(int n, int k) {
    return n % (k + 1);
}

// Grundy for Kayles (bowling pins)
// Can knock down 1 pin or 2 adjacent pins
vector<int> kayles_grundy(int max_n) {
    vector<int> g(max_n + 1, 0);
    int n = 1;
    while (n <= max_n) {
        vector<int> reachable;
        // Remove 1 pin
        if (n >= 1) reachable.push_back(g[n - 1]);
        // Remove 2 adjacent pins
        if (n >= 2) reachable.push_back(g[n - 2]);
        // Split: remove pin i, left and right become independent
        for (int i = 0; i < n; i++) {
            int left = i;
            int right = n - i - 1;
            reachable.push_back(g[left] ^ g[right]);
        }
        g[n] = mex(reachable);
        n++;
    }
    return g;
}

void solve() {
    // Subtraction game: remove 1, 2, or 3
    vector<int> moves = {1, 2, 3};
    auto grundy = compute_grundy_table(20, moves);
    cout << "Grundy numbers (remove 1-3): ";
    for (int i = 0; i <= 20; i++) cout << grundy[i] << " ";
    cout << endl;

    // Wythoff's Game
    cout << "\nWythoff losing positions:" << endl;
    for (int k = 0; k < 8; k++) {
        double phi = (1.0 + sqrt(5.0)) / 2.0;
        int a = (int)(k * phi);
        int b = (int)(k * phi * phi);
        cout << "(" << a << ", " << b << ")" << endl;
    }

    // Kayles
    auto kayles = kayles_grundy(20);
    cout << "\nKayles Grundy: ";
    for (int i = 0; i <= 20; i++) cout << kayles[i] << " ";
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
