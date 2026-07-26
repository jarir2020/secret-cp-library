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

// Classic Nim Game
// Piles of stones, players take turns removing any number from one pile
// XOR of all pile sizes determines winner
// XOR != 0 -> first player wins, XOR == 0 -> second player wins

bool nim_winner(vector<int>& piles) {
    int x = 0;
    int i = 0;
    while (i < (int)piles.size()) {
        x ^= piles[i];
        i++;
    }
    return x != 0;
}

// Find a winning move (if one exists)
// Returns {pile_index, stones_to_remove} or {-1, -1}
pair<int, int> nim_winning_move(vector<int>& piles) {
    int x = 0;
    for (int p : piles) x ^= p;
    if (x == 0) return {-1, -1}; // no winning move

    for (int i = 0; i < (int)piles.size(); i++) {
        int target = piles[i] ^ x;
        if (target < piles[i]) {
            return {i, piles[i] - target};
        }
    }
    return {-1, -1};
}

// Nim with constraints: each pile has a maximum removal limit
// Grundy number for a single pile of size n with max removal k is n % (k+1)
bool nim_with_limit(vector<int>& piles, int max_remove) {
    int x = 0;
    int i = 0;
    while (i < (int)piles.size()) {
        x ^= (piles[i] % (max_remove + 1));
        i++;
    }
    return x != 0;
}

// Multi-pile Nim with different rules per pile
// Grundy[i] = mex of reachable Grundy values from pile i
int compute_grundy(int pile_size, int max_remove) {
    vector<int> grundy(pile_size + 1, 0);
    int i = 1;
    while (i <= pile_size) {
        vector<bool> seen(max_remove + 1, false);
        int j = 1;
        while (j <= max_remove && j <= i) {
            seen[grundy[i - j]] = true;
            j++;
        }
        while (seen[grundy[i]]) grundy[i]++;
        i++;
    }
    return grundy[pile_size];
}

void solve() {
    vector<int> piles = {3, 4, 5};
    cout << "First player wins? " << (nim_winner(piles) ? "Yes" : "No") << endl;

    auto [idx, take] = nim_winning_move(piles);
    if (idx != -1) {
        cout << "Winning move: take " << take << " from pile " << idx << endl;
    }

    vector<int> piles2 = {2, 3, 4};
    cout << "With limit 3, first player wins? " << (nim_with_limit(piles2, 3) ? "Yes" : "No") << endl;

    cout << "Grundy(5, 3) = " << compute_grundy(5, 3) << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
