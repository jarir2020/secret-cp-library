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

// Suffix Automaton — O(n)
// Accepts all substrings of a string
// len: longest string length in the class
// link: longest suffix that is another class
// terminal nodes: store all suffixes
struct SuffixAutomaton {
    struct node {
        int len, link, firstpos;
        map<char, int> nxt;
    };
    int sz, last;
    vector<node> t;
    vector<int> terminal;
    vector<long long> dp;

    SuffixAutomaton(int n) {
        t.resize(2 * n); terminal.resize(2 * n, 0);
        dp.resize(2 * n, -1); sz = 1; last = 0;
        t[0].len = 0; t[0].link = -1; t[0].firstpos = 0;
    }

    void extend(char c) {
        int p = last;
        if (t[p].nxt.count(c)) {
            int q = t[p].nxt[c];
            if (t[q].len == t[p].len + 1) { last = q; return; }
            int clone = sz++;
            t[clone] = t[q]; t[clone].len = t[p].len + 1;
            t[q].link = clone; last = clone;
            while (p != -1 && t[p].nxt[c] == q) { t[p].nxt[c] = clone; p = t[p].link; }
            return;
        }
        int cur = sz++;
        t[cur].len = t[last].len + 1; t[cur].firstpos = t[cur].len;
        p = last;
        while (p != -1 && !t[p].nxt.count(c)) { t[p].nxt[c] = cur; p = t[p].link; }
        if (p == -1) t[cur].link = 0;
        else {
            int q = t[p].nxt[c];
            if (t[p].len + 1 == t[q].len) t[cur].link = q;
            else {
                int clone = sz++;
                t[clone] = t[q]; t[clone].len = t[p].len + 1;
                while (p != -1 && t[p].nxt[c] == q) { t[p].nxt[c] = clone; p = t[p].link; }
                t[q].link = t[cur].link = clone;
            }
        }
        last = cur;
    }

    void build(string& s) {
        for (auto x : s) { extend(x); terminal[last] = 1; }
    }

    // Count distinct substrings
    long long count_substrings() {
        long long ans = 0;
        for (int i = 1; i < sz; i++) ans += t[i].len - t[t[i].link].len;
        return ans;
    }
};

void solve() {
    string s = "abacaba";
    SuffixAutomaton sa(s.size());
    sa.build(s);
    cout << "Distinct substrings of '" << s << "': " << sa.count_substrings() << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
