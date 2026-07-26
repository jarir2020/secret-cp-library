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

// Aho-Corasick — O(N + M + Z) where N=text, M=total pattern length, Z=output
// Multi-pattern string matching automaton (like KMP for multiple patterns)
struct AhoCorasick {
    static const int ALPHA = 26;
    struct Node {
        int children[ALPHA];
        int fail;
        int output;
        vector<int> pattern_ids;
        Node() : fail(0), output(0) { memset(children, -1, sizeof(children)); }
    };

    vector<Node> trie;
    int root;
    vector<int> pattern_len;

    AhoCorasick() { root = 0; trie.emplace_back(); }

    void insert(const string& pattern, int id) {
        int cur = root;
        int i = 0;
        while (i < (int)pattern.size()) {
            int idx = pattern[i] - 'a';
            if (trie[cur].children[idx] == -1) {
                trie[cur].children[idx] = trie.size();
                trie.emplace_back();
            }
            cur = trie[cur].children[idx];
            i++;
        }
        trie[cur].pattern_ids.push_back(id);
        pattern_len.push_back(pattern.size());
    }

    void build() {
        queue<int> q;
        for (int c = 0; c < ALPHA; c++) {
            if (trie[root].children[c] == -1) {
                trie[root].children[c] = root;
            } else {
                trie[trie[root].children[c]].fail = root;
                q.push(trie[root].children[c]);
            }
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int c = 0; c < ALPHA; c++) {
                if (trie[u].children[c] == -1) {
                    trie[u].children[c] = trie[trie[u].fail].children[c];
                } else {
                    trie[trie[u].children[c]].fail = trie[trie[u].fail].children[c];
                    // Merge output links
                    for (int pid : trie[trie[trie[u].children[c]].fail].pattern_ids)
                        trie[trie[u].children[c]].pattern_ids.push_back(pid);
                    q.push(trie[u].children[c]);
                }
            }
        }
    }

    // Returns list of (position, pattern_id) matches
    vector<pair<int, int>> search(const string& text) {
        vector<pair<int, int>> matches;
        int cur = root;
        int i = 0;
        while (i < (int)text.size()) {
            cur = trie[cur].children[text[i] - 'a'];
            int j = 0;
            while (j < (int)trie[cur].pattern_ids.size()) {
                int pid = trie[cur].pattern_ids[j];
                matches.push_back({i - pattern_len[pid] + 1, pid});
                j++;
            }
            i++;
        }
        return matches;
    }
};

void solve() {
    AhoCorasick ac;
    ac.insert("he", 0);
    ac.insert("she", 1);
    ac.insert("his", 2);
    ac.insert("hers", 3);
    ac.build();

    auto matches = ac.search("ahishers");
    cout << "Matches in 'ahishers':" << endl;
    for (auto& [pos, pid] : matches) {
        cout << "  Pattern " << pid << " at position " << pos << endl;
    }
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
