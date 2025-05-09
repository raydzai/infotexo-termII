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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    sch(i, 0, n, 1) sch(j, 0, m, 1) cin >> a[i][j];

    int N = n * m;
    vector< bitset<901> > eqs;
    eqs.reserve(N);

    auto id = [&](int i, int j){ return i * m + j; };

    int di[4] = {1,-1,0,0}, dj[4] = {0,0,1,-1};
    sch(i, 0, n, 1) sch(j, 0, m, 1) if (a[i][j] != -1) {
        bitset<901> row;
        sch(d, 0, 4, 1) {
            int ni = i + di[d], nj = j + dj[d];
            if (ni>=0 && ni<n && nj>=0 && nj<m) {
                row.set(id(ni,nj));
            }
        }
        if (a[i][j] & 1) row.set(N);
        eqs.pub(row);
    }

    int E = eqs.size();
    int rank = 0;
    sch(col, 0, N, 1) {
        int pivot = -1;
        for (int r = rank; r < E; r++) {
            if (eqs[r].test(col)) {
                pivot = r;
                break;
            }
        }
        if (pivot == -1) continue;
        swap(eqs[pivot], eqs[rank]);
        sch(r, 0, E, 1) if (r != rank && eqs[r].test(col)) {
            eqs[r] ^= eqs[rank];
        }
        rank++;
    }

    sch(r, rank, E, 1) {
        if (eqs[r].none() == false && eqs[r].count() == eqs[r].test(N)) {
            cout << 0;
            return 0;
        }
    }

    int free_vars = N - rank;
    // Tính 2^free_vars dưới dạng chuỗi
    vector<int> digits;
    digits.pub(1);
    sch(i, 0, free_vars, 1) {
        int carry = 0;
        for (int &d : digits) {
            int x = d * 2 + carry;
            d = x % 10;
            carry = x / 10;
        }
        if (carry) digits.pub(carry);
    }
    // In kết quả
    for (auto it = digits.rbegin(); it != digits.rend(); ++it) cout << *it;
    return 0;
}
