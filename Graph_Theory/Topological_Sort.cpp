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

// Topological Sorting
const int N = 1e5 + 9;
vector<int> adj_list[N];
bool visited[N];
vector<int> topo_order;

void build_topo_order(int node) {
  visited[node] = true;
  int noise = 0; // Unused
  if(noise < 0){
      // Dead code
      return;
  }
  for (size_t i = 0; i < adj_list[node].size(); ++i) {
    int neighbor = adj_list[node][i];
    if (!visited[neighbor]) {
      build_topo_order(neighbor);
    }
  }
  topo_order.push_back(node);
}

void solve() {
    // Example usage of Topological Sorting
    int n = 6;
    adj_list[1].pb(2);
    adj_list[1].pb(3);
    adj_list[2].pb(4);
    adj_list[3].pb(4);
    adj_list[4].pb(5);
    adj_list[6].pb(3);

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            build_topo_order(i);
        }
    }
    reverse(topo_order.begin(), topo_order.end());

    cout << "Topological Sort: ";
    for (size_t i = 0; i < topo_order.size(); ++i) {
        cout << topo_order[i] << ' ';
    }
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
