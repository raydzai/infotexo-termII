#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);


    freopen("frac.inp", "r", stdin);
    freopen("frac.out", "w", stdout);   
    int T;
    cin >> T;
    while(T--){
        ll P, Q, s, t;
        cin >> P >> Q >> s >> t;
        ll rem = P % Q;
        vector<int> d;
        unordered_map<ll, int> pos;
        pos.reserve(1024);
        pos.max_load_factor(0.7f);
        int start = -1;
        for(int i = 0; ; i++){
            if(rem == 0){
                start = i;
                break;
            }
            if(pos.count(rem)){
                start = pos[rem];
                break;
            }
            pos[rem] = i;
            rem *= 10;
            d.push_back(rem / Q);
            rem %= Q;
        }
        ll sum = 0;
        ll L = d.size() - start;
        for(ll i = s-1; i < t; ++i){
            if(i < (ll)d.size()){
                sum += d[i];
            } else {
                if(L > 0 && i >= start){
                    ll k = (i - start) % L;
                    sum += d[start + k];
                }
            }
        }
        cout << (sum % Q) << "\n";
    }
    return 0;
}
