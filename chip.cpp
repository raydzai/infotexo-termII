#include <bits/stdc++.h>
using namespace std;

int m,n,K;
vector<string> G;
vector<vector<int>> sumBlk;
int dr[4]={-1,1,0,0}, dc[4]={0,0,-1,1};

bool insideSquare(int r,int c,int si,int sj,int L){
    return r>=si && r<si+L && c>=sj && c<sj+L;
}

int getBlk(int si,int sj,int L){
    int i2=si+L-1, j2=sj+L-1;
    return sumBlk[i2+1][j2+1]-sumBlk[si][j2+1]-sumBlk[i2+1][sj]+sumBlk[si][sj];
}

struct HopcroftKarp {
    int N;
    vector<vector<int>> adj;
    vector<int> dist, pairU, pairV;
    const int INF = 1e9;
    HopcroftKarp(int n):N(n),adj(n),dist(n),pairU(n,-1),pairV(n,-1){}
    void addEdge(int u,int v){ adj[u].push_back(v); }
    bool bfs(){
        queue<int> q;
        for(int u=0;u<N;u++){
            if(pairU[u]==-1){ dist[u]=0; q.push(u); }
            else dist[u]=INF;
        }
        bool found=false;
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int v:adj[u]){
                if(pairV[v]==-1) found=true;
                else if(dist[pairV[v]]==INF){
                    dist[pairV[v]] = dist[u]+1;
                    q.push(pairV[v]);
                }
            }
        }
        return found;
    }
    bool dfs(int u){
        for(int v:adj[u]){
            if(pairV[v]==-1 || (dist[pairV[v]]==dist[u]+1 && dfs(pairV[v]))){
                pairU[u]=v;
                pairV[v]=u;
                return true;
            }
        }
        dist[u]=INF;
        return false;
    }
    int maxMatching(){
        int result=0;
        while(bfs()){
            for(int u=0;u<N;u++){
                if(pairU[u]==-1 && dfs(u))
                    result++;
                if(result>=K) return result;
            }
        }
        return result;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("CHIP.INP", "r", stdin);
    freopen("CHIP.OUT", "w", stdout);
    cin>>m>>n>>K;
    G.resize(m);
    for(int i=0;i<m;i++) cin>>G[i];

    sumBlk.assign(m+1, vector<int>(n+1,0));
    for(int i=0;i<m;i++) for(int j=0;j<n;j++){
        sumBlk[i+1][j+1] = sumBlk[i][j+1] + sumBlk[i+1][j] - sumBlk[i][j] + (G[i][j]=='#');
    }

    int lo=0, hi=min(m,n), ans=0;
    while(lo<=hi){
        int mid=(lo+hi)/2;
        bool ok=false;
        for(int si=0;si+mid<=m && !ok;si++){
            for(int sj=0;sj+mid<=n && !ok;sj++){
                if(getBlk(si,sj,mid)>0) continue;
                vector<int> idL(m*n,-1), idR(m*n,-1);
                int cntL=0, cntR=0;
                for(int i=0;i<m;i++) for(int j=0;j<n;j++){
                    if(G[i][j]=='#' || insideSquare(i,j,si,sj,mid)) continue;
                    int idx=i*n+j;
                    if((i+j)%2==0) idL[idx]=cntL++;
                    else idR[idx]=cntR++;
                }
                if(cntL+cntR < 2*K) continue;
                HopcroftKarp hk(cntL);
                for(int i=0;i<m;i++) for(int j=0;j<n;j++){
                    int u=i*n+j;
                    if(idL[u]==-1) continue;
                    for(int d=0;d<4;d++){
                        int ni=i+dr[d], nj=j+dc[d];
                        if(ni<0||ni>=m||nj<0||nj>=n) continue;
                        int v=ni*n+nj;
                        if(idR[v]==-1) continue;
                        hk.addEdge(idL[u], idR[v]);
                    }
                }
                if(hk.maxMatching()>=K){
                    ok=true;
                }
            }
        }
        if(ok){ ans=mid; lo=mid+1; }
        else hi=mid-1;
    }

    cout<<ans<<"\n";
    return 0;
}
