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

ll pm(ll a, ll e, ll mod) {
    ll r = 1;
    while (e) {
        if (e & 1) r = (__int128)r * a % mod;
        a = (__int128)a * a % mod;
        e >>= 1;
    }
    return r;
}

int main() {
    raysiucapvjppro;
    offen("MATKHAU");
    int n; cin >> n;
    vkt<ll> ks; ks.reserve(n);
    sch(i, 0, n, 1) { ll x; cin >> x; ks.pub(x); }
    const ll M = 1000000007;
    ll inv9 = pm(9, M - 2, M);

    const int MAX = 31623;
    vkt<bool> isp(MAX + 1, true);
    isp[0] = isp[1] = false;
    vkt<int> ps; ps.reserve(3400);
    sch(i, 2, MAX + 1, 1) if (isp[i]) {
        ps.pub(i);
        for (int j = i * i; j <= MAX; j += i) isp[j] = false;
    }

    for (ll k : ks) {
        if (k % 2 == 0 || k % 5 == 0) {
            cout << -1 << '\n';
            continue;
        }
        ll t0 = k - 1, tmp = t0;
        vkt<ll> pf;
        pf.pub(2); pf.pub(3);
        for (int p : ps) {
            if ((ll)p * p > tmp) break;
            if (tmp % p == 0) {
                pf.pub(p);
                while (tmp % p == 0) tmp /= p;
            }
        }
        if (tmp > 1) pf.pub(tmp);
        sort(pf.begin(), pf.end());
        pf.erase(unique(pf.begin(), pf.end()), pf.end());

        ll ord = 6 * (k - 1), nmod = 9 * k;
        for (ll p : pf) {
            while (ord % p == 0 && pm(10, ord / p, nmod) == 1) ord /= p;
        }
        ll t = ord;

        ll pow10 = pm(10, t, M);
        ll m_mod = (pow10 + M - 1) % M;
        m_mod = m_mod * inv9 % M;
        ll invk = pm(k, M - 2, M);
        m_mod = m_mod * invk % M;

        cout << m_mod << '\n';
    }
    return 0;
}
