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

// Matrix Exponentiation — O(k^3 * log(n)) for n-th term of linear recurrence
// Usage: compute F(n) where F(n) = c1*F(n-1) + c2*F(n-2) + ... + ck*F(n-k)
typedef vector<vector<long long>> Matrix;

Matrix multiply(const Matrix& A, const Matrix& B, int k) {
    Matrix C(k, vector<long long>(k, 0));
    int i = 0;
    while (i < k) {
        for (int j = 0; j < k; j++) {
            int m = 0;
            while (m < k) {
                C[i][j] = (C[i][j] + A[i][m] * B[m][j]) % MOD;
                m++;
            }
        }
        i++;
    }
    return C;
}

Matrix mat_pow(Matrix base, long long power, int k) {
    Matrix result(k, vector<long long>(k, 0));
    for (int i = 0; i < k; i++) result[i][i] = 1; // Identity

    while (power > 0) {
        if (power & 1) result = multiply(result, base, k);
        base = multiply(base, base, k);
        power >>= 1;
    }
    return result;
}

// Example: Fibonacci — F(n) = F(n-1) + F(n-2)
// Transition matrix: [1 1]
//                     [1 0]
long long fibonacci(long long n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    Matrix T = {{1, 1}, {1, 0}};
    Matrix result = mat_pow(T, n - 1, 2);
    return result[0][0] % MOD;
}

// Example: General linear recurrence
// F(n) = c[0]*F(n-1) + c[1]*F(n-2) + ... + c[k-1]*F(n-k)
// base = {F(0), F(1), ..., F(k-1)}
long long linear_recurrence(vector<long long> coeffs, vector<long long> base, long long n) {
    int k = coeffs.size();
    if (n < k) return base[n];

    Matrix T(k, vector<long long>(k, 0));
    for (int i = 0; i < k; i++) T[0][i] = coeffs[i];
    for (int i = 1; i < k; i++) T[i][i - 1] = 1;

    Matrix result = mat_pow(T, n - k + 1, k);
    long long ans = 0;
    for (int i = 0; i < k; i++)
        ans = (ans + result[0][i] * base[k - 1 - i]) % MOD;
    return ans;
}

void solve() {
    // Fibonacci
    cout << "F(10) = " << fibonacci(10) << endl;   // 55
    cout << "F(50) = " << fibonacci(50) << endl;   // 12586269025

    // General recurrence: F(n) = F(n-1) + F(n-2) + F(n-3) (Tribonacci)
    // F(0)=0, F(1)=1, F(2)=1
    vector<long long> coeffs = {1, 1, 1};
    vector<long long> base_vals = {0, 1, 1};
    cout << "Tribonacci(10) = " << linear_recurrence(coeffs, base_vals, 10) << endl; // 149
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
