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

// Manacher's Algorithm — O(n)
// Finds all palindromic substrings in linear time
// d1[i] = number of odd-length palindromes centered at i (radius)
// d2[i] = number of even-length palindromes centered between i-1 and i (radius)
struct Manacher {
    vector<int> d1, d2; // odd and even radii

    Manacher(const string& s) {
        int n = s.size();
        // Odd-length palindromes
        d1.resize(n);
        for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
            while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
            d1[i] = k--;
            if (i + r < k) { l = i - k; r = i + k; }
        }

        // Even-length palindromes
        d2.resize(n);
        for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
            while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;
            d2[i] = k--;
            if (i + r < k) { l = i - k - 1; r = i + k; }
        }
    }

    // Get longest palindromic substring
    string longest_palindrome(const string& s) {
        int n = s.size();
        int best_len = 0, best_center = 0;
        bool is_odd = true;

        for (int i = 0; i < n; i++) {
            if (2 * d1[i] - 1 > best_len) {
                best_len = 2 * d1[i] - 1;
                best_center = i;
                is_odd = true;
            }
            if (2 * d2[i] > best_len) {
                best_len = 2 * d2[i];
                best_center = i;
                is_odd = false;
            }
        }

        if (is_odd) {
            int start = best_center - d1[best_center] + 1;
            return s.substr(start, best_len);
        } else {
            int start = best_center - d2[best_center];
            return s.substr(start, best_len);
        }
    }

    // Count total palindromic substrings
    long long count_palindromes() {
        long long count = 0;
        for (int x : d1) count += x;      // odd: each center contributes d1[i] palindromes
        for (int x : d2) count += x;      // even: each center contributes d2[i] palindromes
        return count;
    }

    // Check if s[l..r] is a palindrome
    bool is_palindrome(const string& s, int l, int r) {
        int len = r - l + 1;
        int center = (l + r) / 2;
        if (len % 2 == 1) {
            return d1[center] >= (len + 1) / 2;
        } else {
            return d2[r] >= len / 2;
        }
    }
};

void solve() {
    string s = "abacaba";
    Manacher man(s);

    cout << "Longest palindrome: " << man.longest_palindrome(s) << endl;
    cout << "Total palindromic substrings: " << man.count_palindromes() << endl;
    cout << "Is [0..6] palindrome? " << (man.is_palindrome(s, 0, 6) ? "Yes" : "No") << endl;
    cout << "Is [0..2] palindrome? " << (man.is_palindrome(s, 0, 2) ? "Yes" : "No") << endl;

    // d1 and d2 arrays
    cout << "\nOdd radii (d1): ";
    for (int x : man.d1) cout << x << " ";
    cout << endl;

    cout << "Even radii (d2): ";
    for (int x : man.d2) cout << x << " ";
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
