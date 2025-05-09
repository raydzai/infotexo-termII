#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1000000;
static ll x[MAXN], w[MAXN];
static pair<ll,ll> iv[MAXN];
static char ibuf[1<<20]; static int ipos, ilen;

inline char nextChar() {
    if (ipos == ilen) {
        ilen = fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (!ilen) return EOF;
    }
    return ibuf[ipos++];
}

inline bool readInt(int &v) {
    char c; int neg = 0;
    ll x = 0;
    c = nextChar(); if (c == EOF) return false;
    while (c != '-' && (c < '0' || c > '9')) c = nextChar();
    if (c == '-') { neg = 1; c = nextChar(); }
    for (; c >= '0' && c <= '9'; c = nextChar()) x = x * 10 + (c - '0');
    v = neg ? -x : x;
    return true;
}

inline void writeLong(ll x) {
    if (x == 0) {
        putchar('0');
    } else {
        char s[24]; int n = 0;
        while (x) { s[n++] = char('0' + x % 10); x /= 10; }
        while (n--) putchar(s[n]);
    }
    putchar('\n');
}

int main() {
    // đọc/ghi file KIEN.INP, KIEN.OUT
    freopen("KIEN.INP", "r", stdin);
    freopen("KIEN.OUT", "w", stdout);

    int n, k;
    if (!readInt(n) || !readInt(k)) return 0;
    for (int i = 0; i < n; i++) { int t; readInt(t); x[i] = t; }
    for (int i = 0; i < n; i++) { int t; readInt(t); w[i] = t; }

    auto can = [&](ll T) {
        for (int i = 0; i < n; i++) {
            ll d = T / w[i];
            iv[i].first = x[i] - d;
            iv[i].second = x[i] + d;
        }
        sort(iv, iv + n, [](auto &a, auto &b) { return a.second < b.second; });
        int used = 0;
        ll last = LLONG_MIN;
        for (int i = 0; i < n; i++) {
            if (iv[i].first > last) {
                last = iv[i].second;
                if (++used > k) return false;
            }
        }
        return true;
    };

    ll lo = 0, hi = 0;
    ll mn = x[0], mx = x[0];
    for (int i = 1; i < n; i++) {
        mn = min(mn, x[i]);
        mx = max(mx, x[i]);
    }
    for (int i = 0; i < n; i++) {
        ll d1 = llabs(x[i] - mn);
        ll d2 = llabs(x[i] - mx);
        hi = max(hi, w[i] * max(d1, d2));
    }
    
    while (lo < hi) {
        ll mid = lo + ((hi - lo) >> 1);
        if (can(mid)) hi = mid;
        else lo = mid + 1;
    }

    writeLong(lo << 1);
    return 0;
}
