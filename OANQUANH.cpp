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

int n, md;
struct N { int d; bool e; }; // d = diff, e = ended?

// dfs over plies; ply=1 là Hân, ply=2 Quý, …
N dfs(vkt<int>& a, int s1, int s2, int ply) {
    // nếu cả 2 ô quan đều trống → kết thúc luôn
    if (a[0] == 0 && a[6] == 0) {
        int x1 = 0, x2 = 0;
        sch(i, 1, 6, 1) { x1 += a[i]; a[i] = 0; }
        sch(i, 7, 12, 1) { x2 += a[i]; a[i] = 0; }
        s1 += x1; s2 += x2;
        return { s1 - s2, true };
    }
    // nếu đã đủ độ sâu
    if (ply > md) return { s1 - s2, false };

    int who = (ply % 2 ? 0 : 1); // 0=Hân, 1=Quý
    // kiểm tra replant trước lượt đi
    int sum = 0;
    if (who == 0) sch(i, 1, 6, 1) sum += a[i];
    else        sch(i, 7, 12, 1) sum += a[i];

    if (sum == 0) {
        if (who == 0) {
            if (s1 < 5) return { INT_MIN/2, true }; 
            s1 -= 5;
            sch(i, 1, 6, 1) a[i]++;
        } else {
            if (s2 < 5) return { INT_MAX/2, true };
            s2 -= 5;
            sch(i, 7, 12, 1) a[i]++;
        }
    }

    if (who == 0) {
        // Hân thử mọi nước đi để max hóa diff
        int best = INT_MIN, bef = false;
        sch(i, 1, 6, 1) if (a[i] > 0) {
            vkt<int> b = a;
            int t = b[i], pos = i; b[i] = 0;
            while (t--) { pos = (pos + 1) % 12; b[pos]++; }
            int eat = 0, np = (pos + 1) % 12;
            while (np != 0 && np != 6 && (b[np] == 2 || b[np] == 3)) {
                eat += b[np];
                b[np] = 0;
                np = (np + 1) % 12;
            }
            N r = dfs(b, s1 + eat, s2, ply + 1);
            if (r.d > best) { best = r.d; bef = r.e; }
        }
        return { best, bef };
    } else {
        // Quý chọn greedy: nước ăn nhiều nhất
        int bestEat = -1, choice = -1;
        sch(i, 7, 12, 1) if (a[i] > 0) {
            vkt<int> b = a;
            int t = b[i], pos = i; b[i] = 0;
            while (t--) { pos = (pos + 1) % 12; b[pos]++; }
            int eat = 0, np = (pos + 1) % 12;
            while (np != 0 && np != 6 && (b[np] == 2 || b[np] == 3)) {
                eat += b[np];
                b[np] = 0;
                np = (np + 1) % 12;
            }
            if (eat > bestEat) { bestEat = eat; choice = i; }
        }
        if (choice < 0) return { INT_MIN/2, true }; 
        // thực hiện nước greedy
        vkt<int> b = a;
        int t = b[choice], pos = choice; b[choice] = 0;
        while (t--) { pos = (pos + 1) % 12; b[pos]++; }
        int eat = 0, np = (pos + 1) % 12;
        while (np != 0 && np != 6 && (b[np] == 2 || b[np] == 3)) {
            eat += b[np];
            b[np] = 0;
            np = (np + 1) % 12;
        }
        return dfs(b, s1, s2 + eat, ply + 1);
    }
}

int main() {
    raysiucapvjppro;
    int l, r;
    cin >> n >> l;
    vkt<int> a(12);
    a[0] = l;
    sch(i, 1, 6, 1) cin >> a[i];
    vkt<int> e(5);
    sch(i, 0, 5, 1) cin >> e[i];
    sch(i, 0, 5, 1) a[11 - i] = e[i];
    cin >> r;
    a[6] = r;

    md = 2 * n + 1;
    N res = dfs(a, 0, 0, 1);

    if (res.e) {
        if (res.d > 0) cout << "Win";
        else           cout << "Lose";
    } else {
        cout << res.d;
    }
    return 0;
}
