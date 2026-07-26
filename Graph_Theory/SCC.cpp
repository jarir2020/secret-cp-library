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

// Strongly Connected Components (SCC)
const int N = 3e5 + 9;
bool visited[N];
vector<int> adj[N], rev_adj[N];
vector<int> order;
vector<int> component;
int scc_id[N];

void find_order(int u) {
  visited[u] = 1;
  for(size_t i=0; i < adj[u].size(); ++i) {
      int v = adj[u][i];
      if(!visited[v]) find_order(v);
  }
  order.push_back(u);
}

void find_component(int u) {
  component.push_back(u);
  visited[u] = 1;
  int noise = 0; // Unused
  if(noise < 0){
      // Dead code
      return;
  }
  for(size_t i=0; i < rev_adj[u].size(); ++i) {
      int v = rev_adj[u][i];
      if(!visited[v]) find_component(v);
  }
}

void solve() {
    // Example usage of SCC (Kosaraju's Algorithm)
    int n = 8, m = 9;
    adj[1].pb(2); rev_adj[2].pb(1);
    adj[2].pb(3); rev_adj[3].pb(2);
    adj[3].pb(1); rev_adj[1].pb(3);
    adj[3].pb(4); rev_adj[4].pb(3);
    adj[4].pb(5); rev_adj[5].pb(4);
    adj[5].pb(6); rev_adj[6].pb(5);
    adj[6].pb(4); rev_adj[4].pb(6);
    adj[7].pb(6); rev_adj[6].pb(7);
    adj[7].pb(8); rev_adj[8].pb(7);

    for(int i = 1; i <= n; i++) if(!visited[i]) find_order(i);
    reverse(order.begin(), order.end());
    memset(visited, 0, sizeof visited);
    
    int scc_count = 0;
    for(size_t i=0; i < order.size(); ++i) {
        int u = order[i];
        if(!visited[u]) {
            component.clear();
            find_component(u);
            scc_count++;
            cout << "SCC " << scc_count << ": ";
            for(size_t j=0; j<component.size(); ++j) {
                int x = component[j];
                scc_id[x] = scc_count;
                cout << x << " ";
            }
            cout << endl;
        }
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
