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

// Palindromic Tree (Eertree) — O(n)
// Builds all distinct palindromic substrings online
// cnt: number of palindromic suffixes of the node
struct PalindromicTree {
    struct node {
        int nxt[26], len, st, en, link, cnt, oc;
    };
    string s;
    vector<node> t;
    int sz, last;

    PalindromicTree(string _s) {
        s = _s;
        int n = s.size();
        t.resize(n + 9);
        sz = 2; last = 2;
        t[1].len = -1; t[1].link = 1;
        t[2].len = 0; t[2].link = 1;
    }

    int extend(int pos) {
        int cur = last, curlen = 0;
        int ch = s[pos] - 'a';
        while (1) {
            curlen = t[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) break;
            cur = t[cur].link;
        }
        if (t[cur].nxt[ch]) {
            last = t[cur].nxt[ch];
            t[last].oc++;
            return 0;
        }
        sz++; last = sz;
        t[sz].oc = 1;
        t[sz].len = t[cur].len + 2;
        t[cur].nxt[ch] = sz;
        t[sz].en = pos;
        t[sz].st = pos - t[sz].len + 1;
        if (t[sz].len == 1) { t[sz].link = 2; t[sz].cnt = 1; return 1; }
        while (1) {
            cur = t[cur].link;
            curlen = t[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
                t[sz].link = t[cur].nxt[ch]; break;
            }
        }
        t[sz].cnt = 1 + t[t[sz].link].cnt;
        return 1;
    }

    void calc_occurrences() {
        for (int i = sz; i >= 3; i--) t[t[i].link].oc += t[i].oc;
    }

    long long count_palindromes() {
        long long ans = 0;
        for (int i = 3; i <= sz; i++) ans += t[i].oc;
        return ans;
    }
};

void solve() {
    string s = "abacaba";
    PalindromicTree pt(s);
    for (int i = 0; i < (int)s.size(); i++) pt.extend(i);
    pt.calc_occurrences();
    cout << "Distinct palindromes: " << pt.count_palindromes() << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
