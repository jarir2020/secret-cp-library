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

// Count inversions using merge sort — O(n log n)
// An inversion is a pair (i, j) where i < j and arr[i] > arr[j]
long long count_inversions(vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) return 0;

    int mid = n / 2;
    vector<int> left(arr.begin(), arr.begin() + mid);
    vector<int> right(arr.begin() + mid, arr.end());

    long long inv = count_inversions(left) + count_inversions(right);

    int i = 0, j = 0, k = 0;
    while (i < (int)left.size() && j < (int)right.size()) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            inv += left.size() - i;  // all remaining in left are > right[j]
            arr[k++] = right[j++];
        }
    }
    while (i < (int)left.size()) arr[k++] = left[i++];
    while (j < (int)right.size()) arr[k++] = right[j++];

    return inv;
}

// Count inversions using BIT — O(n log n)
// Useful when values are bounded
long long count_inversions_bit(vector<int>& arr) {
    int n = arr.size();
    vector<int> sorted_arr = arr;
    sort(sorted_arr.begin(), sorted_arr.end());
    sorted_arr.erase(unique(sorted_arr.begin(), sorted_arr.end()), sorted_arr.end());

    auto get_idx = [&](int x) {
        return lower_bound(sorted_arr.begin(), sorted_arr.end(), x) - sorted_arr.begin() + 1;
    };

    int m = sorted_arr.size();
    vector<int> bit(m + 1, 0);

    auto update = [&](int i) { for (; i <= m; i = i + i & -i) bit[i]++; };
    auto query = [&](int i) { int s = 0; for (; i > 0; i -= i & -i) s = s + bit[i]; return s; };

    long long inv = 0;
    int i = n - 1;
    while (i >= 0) {
        int idx = get_idx(arr[i]);
        inv += query(idx - 1);
        update(idx);
        i--;
    }
    return inv;
}

void solve() {
    vector<int> arr = {2, 4, 3, 1, 5};
    vector<int> arr2 = arr; // copy for BIT version
    cout << "Inversions (merge sort): " << count_inversions(arr) << endl;  // 5
    cout << "Inversions (BIT): " << count_inversions_bit(arr2) << endl;    // 5
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) { solve(); }
    return 0;
}
