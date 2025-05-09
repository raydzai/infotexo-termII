#include <bits/stdc++.h>
#define sch(i, a, b, c) for (int i = a; i < b; i += c)
#define ll long long
using namespace std;

ll mod, B;
pair<ll,ll> f(ll n){
    if(n==0) return {0,1%mod};
    if(n%2==0){
        auto t = f(n/2);
        ll S = t.first, P = t.second;
        ll S2 = (__int128)S * ((1 + P) % mod) % mod;
        ll P2 = (__int128)P * P % mod;
        return {S2, P2};
    } else {
        auto t = f(n-1);
        ll S = t.first, P = t.second;
        ll S2 = (S + P) % mod;
        ll P2 = (__int128)P * B % mod;
        return {S2, P2};
    }
}

ll pw(ll a, ll e){
    ll r = 1 % mod;
    while(e){
        if(e&1) r = (__int128)r * a % mod;
        a = (__int128)a * a % mod;
        e >>= 1;
    }
    return r;
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    freopen("sodu.inp", "r", stdin);
    freopen("sodu.out", "w", stdout);
    int T; cin >> T;
    sch(i, 0, T, 1){
        ll x, n, m; cin >> x >> n >> m;
        mod = m;
        ll t = x, d = 0;
        while(t){ d++; t /= 10; }
        B = pw(10 % mod, d);
        ll sum = f(n).first;
        ll ans = (__int128)(x % mod) * sum % mod;
        cout << ans << "\n";
    }
    return 0;
}
