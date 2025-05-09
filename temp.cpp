#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;

    int k = 1;
    while ((k * (k + 1)) / 2 < N) {
        k++;
    }
    
    int prev_total = (k - 1) * k / 2;
    
    int m = N - prev_total;

    int L = 1; 
    int b = 1; 

    for (int i = 2; i <= k; i++) {
        b = ((L / i) + 1) * i;
        L = b + (i - 1) * i;
    }

    int result = b + (m - 1) * k;

    cout << result << endl;

    return 0;
}
