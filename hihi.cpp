#include <bits/stdc++.h>

using namespace std;

int main(){
    int n; cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    int result = 0;
    for (int i = 0; i < n; i++){
        string s = to_string(a[i]);
        bool check = true;
        for (char i : s){
            if (i == '2' || i == '3' || i == '5' || i == '7'){
                check = true;
            }
            else if (i == '1' || i == '0' || i == '4' || i == '6' || i == '8' || i == '9'){
                check = false;
                break;
            }
        }
        if (check) result++;
    }

    cout << result;
    return 0;
}