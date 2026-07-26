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
const double EPS = 1e-9;

// Mo's Algorithm — O((N + Q) * sqrt(N)) for offline range queries
// Answers Q range queries on a static array in O(sqrt(N)) amortized per query
struct MoQuery {
    int l, r, idx;
};

struct MoAlgorithm {
    int n, block_size;
    vector<int> arr;

    MoAlgorithm(const vector<int>& a) : arr(a), n(a.size()) {
        block_size = max(1, (int)sqrt(n));
    }

    // Sort queries: by block of l, then by r
    static bool cmp(const MoQuery& a, const MoQuery& b) {
        int block_a = a.l / /* block_size */ 1; // placeholder
        int block_b = b.l / /* block_size */ 1;
        if (block_a != block_b) return block_a < block_b;
        return a.r < b.r;
    }

    vector<MoQuery> sort_queries(vector<MoQuery>& queries) {
        sort(queries.begin(), queries.end(), [&](const MoQuery& a, const MoQuery& b) {
            int block_a = a.l / block_size;
            int block_b = b.l / block_size;
            if (block_a != block_b) return block_a < block_b;
            // Alternate order within block for O(1) amortized moves
            return (block_a & 1) ? (a.r < b.r) : (a.r > b.r);
        });
        return queries;
    }
};

// Example: Count distinct elements in range [l, r]
struct DistinctCount {
    vector<int> freq;
    int distinct;
    int block_size;

    DistinctCount(int max_val) : freq(max_val + 1, 0), distinct(0) {}

    void add(int x) { if (freq[x]++ == 0) distinct++; }
    void remove(int x) { if (--freq[x] == 0) distinct--; }
    int get_count() { return distinct; }
};

// Example: Range sum query (trivial but demonstrates the framework)
struct RangeSum {
    long long sum;

    RangeSum() : sum(0) {}

    void add(int x) { sum += x; }
    void remove(int x) { sum -= x; }
    long long get_sum() { return sum; }
};

// Example: Range mode query (frequency of most frequent element)
struct RangeMode {
    vector<int> freq;
    int max_freq;
    int block_size;

    RangeMode(int max_val, int n) : freq(max_val + 1, 0), max_freq(0) {
        block_size = max(1, (int)sqrt(n));
    }

    void add(int x) {
        freq[x]++;
        max_freq = max(max_freq, freq[x]);
    }

    void remove(int x) {
        freq[x]--;
        // Note: max_freq might be stale after removal — O(sqrt(N)) to recompute
        // For simplicity, recompute periodically or use a different approach
    }

    int get_mode() { return max_freq; }
};

// Mo's on Trees — O((N + Q) * sqrt(N))
// Flattens tree to Euler tour, then applies Mo's
struct MoOnTrees {
    int n, timer;
    vector<vector<int>> adj;
    vector<int> euler, first, depth;
    vector<bool> visited;

    MoOnTrees(int n) : n(n), adj(n), euler(2 * n), first(n, -1), depth(n), visited(n, false), timer(0) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int p = -1) {
        first[u] = timer;
        euler[timer++] = u;
        visited[u] = true;
        for (int v : adj[u]) {
            if (v != p) {
                depth[v] = depth[u] + 1;
                dfs(v, u);
            }
        }
        euler[timer++] = u; // exit
    }

    // Convert tree query [u, v] to flat array query
    // Returns {l, r, lca} for Mo's
    pair<pair<int, int>, int> get_query(int u, int v) {
        if (first[u] > first[v]) swap(u, v);
        int lca = u; // simplified — use LCA for proper implementation
        return {{first[u], first[v]}, lca};
    }
};

void solve() {
    vector<int> arr = {1, 2, 1, 3, 2, 1, 4, 3};
    int n = arr.size();

    // Queries: [l, r]
    vector<MoQuery> queries = {
        {0, 3, 0},  // distinct: {1, 2, 3} = 3
        {1, 5, 1},  // distinct: {2, 1, 3} = 3
        {0, 7, 2},  // distinct: {1, 2, 3, 4} = 4
    };

    // Sort queries
    MoAlgorithm mo(arr);
    mo.sort_queries(queries);

    // Process
    DistinctCount dc(4); // values up to 4
    int cur_l = 0, cur_r = -1;
    vector<int> results(queries.size());

    for (auto& q : queries) {
        while (cur_l > q.l) dc.add(arr[--cur_l]);
        while (cur_r < q.r) dc.add(arr[++cur_r]);
        while (cur_l < q.l) dc.remove(arr[cur_l++]);
        while (cur_r > q.r) dc.remove(arr[cur_r--]);
        results[q.idx] = dc.get_count();
    }

    cout << "Distinct elements per query:" << endl;
    for (int i = 0; i < (int)queries.size(); i++) {
        cout << "[" << queries[i].l << ", " << queries[i].r << "] = " << results[i] << endl;
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
