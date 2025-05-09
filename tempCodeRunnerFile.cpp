#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;

int n, m;
vector<string> A;
vector<int> disc, low, subsize, removed;
vector<bool> isZero;
int T = 0;
int di[4] = {1,-1,0,0}, dj[4] = {0,0,1,-1};


inline int id(int i,int j){ return i*m + j; }


void dfs(int u, int parent) {
    disc[u] = low[u] = ++T;
    subsize[u] = 1;
    removed[u] = 1;        
    for(int k=0; k<4; k++){
        int i = u/m + di[k], j = u%m + dj[k];
        if (i<0||i>=n||j<0||j>=m) continue;
        int v = id(i,j);
        if (!isZero[v]) continue;
        if (disc[v]==0) {
            dfs(v, u);
            subsize[u] += subsize[v];
            low[u] = min(low[u], low[v]);
            
            if (low[v] >= disc[u]) {
                
                removed[u] += subsize[v];
            }
        }
        else if (v != parent) {
            low[u] = min(low[u], disc[v]);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("binmat.inp", "r", stdin);
    freopen("binmat.out", "w", stdout);
    cin >> n >> m;
    A.resize(n);
    for(int i=0; i<n; i++) {
        A[i].resize(m);
        for(int j=0; j<m; j++){
            char c; cin >> c;
            A[i][j] = c;
        }
    }

    int totalZeros = 0, totalOnes = 0;
    isZero.assign(n*m, false);
    for(int i=0; i<n; i++) for(int j=0; j<m; j++){
        if (A[i][j]=='0') {
            isZero[id(i,j)] = true;
            totalZeros++;
        } else totalOnes++;
    }

    
    int N = n*m;
    disc.assign(N,0);
    low.assign(N,0);
    subsize.assign(N,0);
    removed.assign(N,0);

    
    
    
    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            int u = id(i,j);
            if (!disc[u] && A[i][j]=='0' &&
               (i==0||i==n-1||j==0||j==m-1))
            {
                dfs(u, -1);
                
                i=n; break;
            }
        }
    }

    
    int best = 0;
    for(int u=0; u<N; u++){
        if (isZero[u]) best = max(best, removed[u]);
    }

    
    cout << totalOnes + best << "\n";
    return 0;
}
