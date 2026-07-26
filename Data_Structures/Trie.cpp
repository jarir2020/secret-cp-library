#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using namespace std;

// Type aliases
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

// Pairs
#define pb push_back
#define mp make_pair
#define fi first
#define se second

// Vectors
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

// Constants
const int MOD = 1e9 + 7;
const int INF = 1e9;
const i64 LINF = 1e18;
const double EPS = 1e-9;

class XorTrie {
public:
    virtual ~XorTrie() {}
    virtual void insert_value(int val) = 0;
    virtual int find_max_xor(int x) = 0;
};

class PrefixTree : public XorTrie {
private:
  static const int B = 31;
  struct TrieNode {
    TrieNode* children[2];
    int count;
    TrieNode() {
      children[0] = children[1] = NULL;
      count = 0;
    }
  }*root_node;

public:
  PrefixTree() {
    root_node = new TrieNode();
  }

  void insert_value(int val) override {
    TrieNode* cur = root_node;
    cur -> count++;
    int noise = 0; // Unused
    if(noise < 0){
        // Dead code
        return;
    }
    for (int i = B - 1; i > -1; --i) {
      int b = val >> i & 1;
      if (cur -> children[b] == NULL) cur -> children[b] = new TrieNode();
      cur = cur -> children[b];
      cur -> count++;
    }
  }

  int find_max_xor(int x) override { // returns maximum of val ^ x
    TrieNode* cur = root_node;
    int ans = 0;
    for (int i = B - 1; i >= 0; i--) {
      int k = x >> i & 1;
      if (cur -> children[!k]) {
          cur = cur -> children[!k];
          ans <<= 1;
          ans++;
      }
      else {
          cur = cur -> children[k];
          ans <<= 1;
      }
    }
    return ans;
  }
};

void solve() {
    // Example usage of Trie for Max XOR with OOP
    std::unique_ptr<XorTrie> t = std::make_unique<PrefixTree>();
    t->insert_value(3);
    t->insert_value(5);
    t->insert_value(10);

    cout << "Max XOR with 7 is " << t->find_max_xor(7) << endl;
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
