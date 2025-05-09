#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    
    freopen("CHIAKEO.INP", "r", stdin);
    freopen("CHIAKEO.OUT", "w", stdout);

    int N;
    cin >> N;
    vector<int> rating(N);
    for (int i = 0; i < N; i++) {
        cin >> rating[i];
    }

    
    vector<long long> candy(N, 1);

    
    for (int i = 1; i < N; i++) {
        if (rating[i] > rating[i-1]) {
            candy[i] = candy[i-1] + 1;
        }
    }

    
    for (int i = N-2; i >= 0; i--) {
        if (rating[i] > rating[i+1]) {
            candy[i] = max(candy[i], candy[i+1] + 1);
        }
    }

    
    long long total = 0;
    for (auto x : candy) total += x;

    cout << total << "\n";
    return 0;
}

// Trường hợp n ≤ k: Trả về b[n-1].
// Trường hợp n > k:
// 1. Xây dựng ma trận M kích thước k x k:
// - Dòng đầu tiên: chứa các hệ số c1, c2, ..., ck.
// - Các dòng còn lại: ma trận đơn vị dịch xuống (M[i][i-1] = 1).
// 2. Tính P = M^(n-k) bằng phương pháp bình phương lặp.
// 3. Tính a_n: Tổng của dòng đầu tiên của ma trận P nhân với vector [b[k-1], b[k-2], ..., b[0]].
// 4. Modulo: Tất cả phép tính được thực hiện modulo 10^9.