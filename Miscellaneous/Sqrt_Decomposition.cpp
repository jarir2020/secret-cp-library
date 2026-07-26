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

// Sqrt Decomposition — O(sqrt(n)) per query
// Decomposes array into blocks of size sqrt(n)
struct SqrtDecomposition {
    int n, block_size, num_blocks;
    vector<long long> arr;
    vector<long long> block_sum;
    vector<long long> block_lazy;

    SqrtDecomposition(vector<long long>& a) : arr(a) {
        n = a.size();
        block_size = max(1, (int)sqrt(n));
        num_blocks = (n + block_size - 1) / block_size;
        block_sum.assign(num_blocks, 0);
        block_lazy.assign(num_blocks, 0);
        for (int i = 0; i < n; i++)
            block_sum[i / block_size] += a[i];
    }

    // Range add: add val to arr[l..r] — O(sqrt(n))
    void range_add(int l, int r, long long val) {
        int bl = l / block_size, br = r / block_size;
        if (bl == br) {
            for (int i = l; i <= r; i++) {
                arr[i] += val;
                block_sum[bl] += val;
            }
            return;
        }
        // Left partial block
        for (int i = l; i < (bl + 1) * block_size; i++) {
            arr[i] += val;
            block_sum[bl] += val;
        }
        // Full blocks
        for (int b = bl + 1; b < br; b++) {
            block_lazy[b] += val;
            block_sum[b] += val * block_size;
        }
        // Right partial block
        for (int i = br * block_size; i <= r; i++) {
            arr[i] += val;
            block_sum[br] += val;
        }
    }

    // Range sum query: sum of arr[l..r] — O(sqrt(n))
    long long range_sum(int l, int r) {
        int bl = l / block_size, br = r / block_size;
        long long result = 0;
        if (bl == br) {
            for (int i = l; i <= r; i++)
                result += arr[i] + block_lazy[bl];
            return result;
        }
        for (int i = l; i < (bl + 1) * block_size; i++)
            result += arr[i] + block_lazy[bl];
        for (int b = bl + 1; b < br; b++)
            result += block_sum[b];
        for (int i = br * block_size; i <= r; i++)
            result += arr[i] + block_lazy[br];
        return result;
    }

    // Point query
    long long point_query(int idx) {
        return arr[idx] + block_lazy[idx / block_size];
    }
};

// Mo's Algorithm is in Data_Structures/Mos_Algorithm.cpp
// This is the block-based decomposition for online queries




void solve() {
    vector<long long> arr = {1, 2, 3, 4, 5, 6, 7, 8};
    SqrtDecomposition sd(arr);

    cout << "Sum [1..4]: " << sd.range_sum(1, 4) << endl;  // 14

    sd.range_add(2, 5, 3); // add 3 to arr[2..5]
    cout << "After add, sum [1..4]: " << sd.range_sum(1, 4) << endl;  // 20

    cout << "Point query arr[3]: " << sd.point_query(3) << endl;  // 10
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
