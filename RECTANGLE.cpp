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

int main() {
    raysiucapvjppro;
    offen("RECTANGLE");
    ll m; int n;
    cin >> m >> n;
    vkt<int> a(n);
    sch(i, 0, n, 1) cin >> a[i];
    vkt<int> b(n);
    sch(i, 0, n, 1) b[i] = m - a[i];

    auto solve = [&](vkt<int>& v) {
        ll ans = 0;
        vkt<int> st;
        sch(i, 0, n + 1, 1) {
            int cur = (i == n ? 0 : v[i]);
            while (!st.empty() && cur < v[st.back()]) {
                int tp = st.back(); st.pob();
                ll h = v[tp];
                ll w = st.empty() ? i : i - st.back() - 1;
                ans = max(ans, h * w);
            }
            st.pub(i);
        }
        return ans;
    };

    cout << max(solve(a), solve(b));
    return 0;
}
