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

const ll A = 1e5;
ll B, C;
vkt<vkt<pair<ll, ll>>> D(A + 1);
vkt<tuple<ll, ll, ll>> E;

vkt<ll> F(ll G, ll H) {
    vkt<ll> I(B + 1, LLONG_MAX);
    priority_queue<pair<ll, ll>, vkt<pair<ll, ll>>, greater<>> J;

    J.push({0, G});
    I[G] = 0;

    while (!J.empty()) {
        auto [K, L] = J.top(); J.pop();
        if (K > I[L]) continue;

        for (auto [M, N] : D[L]) {
            ll O = K + N;
            if (O < I[M]) {
                I[M] = O;
                J.push({O, M});
            }
        }
    }
    return I;
}

struct P {
    vkt<vkt<ll>> Q;
    vkt<ll> R, S, T;
    P(ll U) : Q(U + 1), R(U + 1), S(U + 1, LLONG_MAX), T(U + 1, LLONG_MAX) {}

    void V(ll W, ll X) {
        Q[W].pub(X);
        R[X]++;
    }

    void Y(const vkt<ll> &Z, const vkt<ll> &AA, ll &AB) {
        S = Z;
        T = AA;
        queue<ll> AC;
        sch(AD, 1, B + 1, 1) {
            if (R[AD] == 0) AC.push(AD);
        }

        while (!AC.empty()) {
            ll AE = AC.front(); AC.pop();
            AB = min(AB, S[AE] + T[AE]);

            for (ll AF : Q[AE]) {
                S[AF] = min(S[AF], S[AE]);
                R[AF]--;
                if (R[AF] == 0) AC.push(AF);
            }
        }
    }
};

int main() {
    raysiucapvjppro;
    offen("bus");

    cin >> B >> C;
    ll G, H, I, J; cin >> G >> H >> I >> J;

    while (C--) {
        ll K, L, M; cin >> K >> L >> M;
        D[K].pub({L, M});
        D[L].pub({K, M});
        E.pub({K, L, M});
    }

    vkt<ll> N = F(G, H);
    vkt<ll> O = F(H, G);
    vkt<ll> P1 = F(I, J);
    vkt<ll> Q1 = F(J, I);

    ll R1 = N[H], S = P1[J];

    P T1(B), U1(B);

    for (auto [V1, W1, X1] : E) {
        if (N[V1] + X1 + O[W1] == R1) {
            T1.V(V1, W1);
            U1.V(W1, V1);
        }
        if (N[W1] + X1 + O[V1] == R1) {
            T1.V(W1, V1);
            U1.V(V1, W1);
        }
    }

    T1.Y(P1, Q1, S);
    U1.Y(P1, Q1, S);

    cout << S;
    return 0;
}
