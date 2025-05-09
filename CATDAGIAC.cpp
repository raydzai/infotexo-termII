#include <bits/stdc++.h>
#define sch(i, a, b, c) for (int i = a; i < b; i += c)
#define fel(i, a, b, c) for (int i = a; i > b; i -= c)
#define ll long long
#define ull unsigned long long
#define str string
#define vkt vector
#define rv(a) reverse(a.begin(), a.end())
#define pub push_back
#define pob pop_back
#define raysiucapvjppro ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define offen(file_name) freopen(file_name ".inp", "r", stdin), freopen(file_name ".out", "w", stdout);

using namespace std;

const int MOD = 1000000007;
int fact[300], invfact[300];

ll modpow(ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int C(int n, int r) {
    if (r < 0 || r > n) return 0;
    return (ll)fact[n] * invfact[r] % MOD * invfact[n - r] % MOD;
}

int main() {
    raysiucapvjppro;
    offen("CATDAGIAC");
    int N, M;
    cin >> N >> M;
    int k = M - 1;
    int up = N + k;
    fact[0] = 1;
    sch(i, 1, up + 1, 1) fact[i] = (ll)fact[i - 1] * i % MOD;
    invfact[up] = modpow(fact[up], MOD - 2);
    for (int i = up; i > 0; --i) invfact[i - 1] = (ll)invfact[i] * i % MOD;
    ll ans = (ll)C(N - 3, k) * C(N + k - 1, k) % MOD * modpow(k + 1, MOD - 2) % MOD;
    cout << ans;
    return 0;
}
