#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

pair<int64, int64> fib_pair(int64 n, int64 m) {
    if (n == 0) return {0, 1};
    auto p = fib_pair(n >> 1, m);
    int64 a = p.first, b = p.second;
    int64 c = (a * ((b * 2 - a + m) % m)) % m;
    int64 d = ((a * a) % m + (b * b) % m) % m;
    if (n & 1)
        return {d, (c + d) % m};
    else
        return {c, d};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int64 n, i, k;
        cin >> n >> i >> k;

        auto p = fib_pair(i, k);
        int64 fi = p.first, fi1 = p.second;

        unordered_map<int64, int> first_pos;
        first_pos.reserve(k * 2);
        int64 cur = 0;
        int64 a = fi, b = fi1;
        bool found = false;

        for (int j = 1; j <= k; j++) {
            cur = (cur + a) % k;
            if (cur == 0) {
                cout << j;
                for (int64 x = 0; x < j; x++) {
                    cout << ' ' << (i + x);
                }
                cout << "\n";
                found = true;
                break;
            }
            if (first_pos.count(cur)) {
                int p0 = first_pos[cur];
                int q = j - p0;
                cout << q;
                for (int64 x = p0; x < j; x++) {
                    cout << ' ' << (i + x);
                }
                cout << "\n";
                found = true;
                break;
            }
            first_pos[cur] = j;

            int64 c = (a + b) % k;
            a = b;
            b = c;
        }

        if (!found) {
            cout << 0 << "\n";
        }
    }
    return 0;
}
