#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1000000007;

vector<ll> convolve(const vector<ll>& A, const vector<ll>& B, int m) {
    vector<ll> C(m);
    for (int i = 0; i < m; ++i) if (A[i]) {
        for (int j = 0; j < m; ++j) if (B[j]) {
            int k = i + j;
            if (k >= m) k %= m;
            C[k] = (C[k] + A[i] * B[j]) % MOD;
        }
    }
    return C;
}

vector<ll> power(vector<ll> base, long long exp, int m) {
    vector<ll> result(m);
    
    result[0] = 1;
    while (exp > 0) {
        if (exp & 1) result = convolve(result, base, m);
        base = convolve(base, base, m);
        exp >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    long long l;
    cin >> n >> l >> m;

    vector<ll> begin_cnt(m), mid_cnt(m), end_cnt(m);
    vector<int> a(n);

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        begin_cnt[x % m]++;
    }
    
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        mid_cnt[a[i] % m]++;
    }
    
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        end_cnt[(x + a[i]) % m]++;
    }

    vector<ll> total;
    if (l >= 3) {
        auto mid_pow = power(mid_cnt, l - 2, m);
        
        total = convolve(begin_cnt, mid_pow, m);
        total = convolve(total, end_cnt, m);
    } else {
        total = convolve(begin_cnt, end_cnt, m);
    }
    
    cout << total[0] << "\n";
    return 0;
}
