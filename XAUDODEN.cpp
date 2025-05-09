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
ll modexp(ll a, ll e=MOD-2){
    ll r=1;
    while(e){
        if(e&1) r=r*a%MOD;
        a=a*a%MOD;
        e>>=1;
    }
    return r;
}
int main(){
    raysiucapvjppro;
    offen("XAUDODEN");
    int A,B,C,D;
    cin>>A>>B>>C>>D;
    // kiểm tra khả thi
    if      (B==D+1){}
    else if (D==B+1){}
    else if (B==D){}
    else{
        cout<<0;
        return 0;
    }
    // tính N = max(A+B, C+max(B,D)) + 5
    int M = max(A+B, C+max(B,D)) + 5;
    vkt<ll> fac(M+1), ifac(M+1);
    fac[0]=1;
    sch(i,1,M+1,1) fac[i]=fac[i-1]*i%MOD;
    ifac[M]=modexp(fac[M]);
    for(int i=M;i>0;--i) ifac[i-1]=ifac[i]*i%MOD;
    auto Cn = [&](int n,int k)->ll{
        if(k<0||k>n) return 0;
        return fac[n]*ifac[k]%MOD*ifac[n-k]%MOD;
    };
    ll ans=0;
    int k = B + D + 1;
    if(B==D){
        // start = R
        int r1 = (k+1)/2, b1 = k/2;
        int x1 = A + r1, y1 = C + b1;
        ll w1 = Cn(x1-1, r1-1) * Cn(y1-1, b1-1) % MOD;
        // start = B
        int r2 = k/2, b2 = (k+1)/2;
        int x2 = A + r2, y2 = C + b2;
        ll w2 = Cn(x2-1, r2-1) * Cn(y2-1, b2-1) % MOD;
        ans = (w1 + w2) % MOD;
    } else if (B==D+1){
        // start R end B
        int r = k/2 + 1, b = k/2 + 0;
        // but since k even = 2D+2, k/2=D+1 so r=b=D+1
        r = D+1; b = D+1;
        int x = A + r, y = C + b;
        ans = Cn(x-1, r-1) * Cn(y-1, b-1) % MOD;
    } else if (D==B+1){
        // start B end R
        int b = B+1, r = B+1;
        int x = A + r, y = C + b;
        ans = Cn(x-1, r-1) * Cn(y-1, b-1) % MOD;
    }
    cout<<ans;
    return 0;
}
