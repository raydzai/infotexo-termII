#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;

int n, m;
vector<string> a;
vector<vector<int>> disc, low, sz;
vector<vector<bool>> vis, isBorder, vis0;
vector<vector<long long>> extra;
int ti = 0, total0 = 0;
int dx[4] = {1,-1,0,0}, dy[4] = {0,0,1,-1};

bool in(int x, int y){ return 0<=x&&x<n&&0<=y&&y<m; }


void dfs(int x, int y, int px, int py){
    vis[x][y] = true;
    disc[x][y] = low[x][y] = ++ti;
    sz[x][y] = 1;
    isBorder[x][y] = (x==0||x==n-1||y==0||y==m-1);
    bool firstChild = true;
    for(int k=0;k<4;k++){
        int nx = x+dx[k], ny = y+dy[k];
        if(!in(nx,ny) || a[nx][ny]!='0') continue;
        if (!vis[nx][ny]) {
            dfs(nx,ny,x,y);
            sz[x][y] += sz[nx][ny];
            isBorder[x][y] = isBorder[x][y] || isBorder[nx][ny];
            low[x][y] = min(low[x][y], low[nx][ny]);
            
            if (low[nx][ny] >= disc[x][y] && !isBorder[nx][ny]) {
                extra[x][y] += sz[nx][ny];
            }
        }
        else if (!(nx==px && ny==py)) {
            low[x][y] = min(low[x][y], disc[nx][ny]);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("binmat.inp", "r", stdin);
    freopen("binmat.out", "w", stdout);
    cin >> n >> m;
    a.resize(n);
    for(int i=0;i<n;i++){
        a[i].resize(m);
        for(int j=0;j<m;j++){
            char c; cin >> c;
            a[i][j] = c;
            if (c=='0') total0++;
        }
    }

    disc.assign(n, vector<int>(m,0));
    low   = disc;
    sz    = disc;
    vis   = vector<vector<bool>>(n, vector<bool>(m,false));
    isBorder = vis;
    extra = vector<vector<long long>>(n, vector<long long>(m,0));

    
    for(int i=0;i<n;i++) for(int j=0;j<m;j++){
        if (a[i][j]=='0' && (i==0||i==n-1||j==0||j==m-1)) {
            dfs(i,j,-1,-1);
            goto DONE;
        }
    }
DONE:;

    long long baseOnes = 1LL*n*m - total0;
    long long bestExtra = 1;  
    for(int i=0;i<n;i++) for(int j=0;j<m;j++){
        if (a[i][j]=='0') {
            bestExtra = max(bestExtra, extra[i][j] + 1);
        }
    }

    cout << (baseOnes + bestExtra) << "\n";
    return 0;
}
