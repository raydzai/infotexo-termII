#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MAX_R = 1e11;
unordered_map<ll, int> primitive_count;

ll gcd(ll a, ll b) {
    while (b) tie(a, b) = make_pair(b, a % b);
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("count.inp", "r", stdin);
    freopen("count.out", "w", stdout);
    ll l, r;
    cin >> l >> r;

    
    ll max_m = sqrt(MAX_R / 2.0) + 1;

    for (ll m = 2; m <= max_m; ++m) {
        for (ll n = (m & 1 ? 2 : 1); n < m; n += 2) {
            if (gcd(m, n) != 1) continue;

            ll p = 2 * m * (m + n);
            if (p > r) break;

            primitive_count[p]++;
        }
    }

    
    ll res = 0;
    for (auto &[p, cnt] : primitive_count) {
        ll k_min = (l + p - 1) / p;
        ll k_max = r / p;
        if (k_max >= k_min) {
            res += cnt * (k_max - k_min + 1);
        }
    }

    cout << res << '\n';
    return 0;
}
