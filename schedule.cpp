#include <bits/stdc++.h>
using namespace std;

// MaxFlow Edmonds–Karp
struct Edge {
    int v, cap, rev;
};
struct MaxFlow {
    int N;
    vector<vector<Edge>> G;
    vector<int> level, ptr;
    MaxFlow(int n): N(n), G(n), level(n), ptr(n) {}
    void addEdge(int u, int v, int c) {
        G[u].push_back({v,c,(int)G[v].size()});
        G[v].push_back({u,0,(int)G[u].size()-1});
    }
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q; q.push(s);
        level[s]=0;
        while(!q.empty()) {
            int u=q.front(); q.pop();
            for(auto &e:G[u]){
                if(level[e.v]<0 && e.cap>0){
                    level[e.v]=level[u]+1;
                    q.push(e.v);
                }
            }
        }
        return level[t]>=0;
    }
    int dfs(int u, int t, int f) {
        if(!f||u==t) return f;
        for(int &i=ptr[u]; i<(int)G[u].size(); i++){
            auto &e=G[u][i];
            if(level[e.v]==level[u]+1 && e.cap>0){
                if(int pushed=dfs(e.v,t,min(f,e.cap))){
                    e.cap-=pushed;
                    G[e.v][e.rev].cap += pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }
    int maxflow(int s, int t) {
        int flow=0;
        while(bfs(s,t)){
            fill(ptr.begin(), ptr.end(), 0);
            while(int pushed=dfs(s,t,INT_MAX)){
                flow+=pushed;
            }
        }
        return flow;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("schedule.inp", "r", stdin);
    freopen("schedule.out", "w", stdout);
    int T; 
    cin>>T;
    while(T--){
        int n; 
        cin>>n;
        vector<vector<int>> pred(n+1), succ(n+1);
        string line;
        getline(cin,line); // bỏ phần còn dòng
        for(int i=1;i<=n;i++){
            getline(cin,line);
            stringstream ss(line);
            int x;
            while(ss>>x && x!=0){
                pred[i].push_back(x);
                succ[x].push_back(i);
            }
        }

        // 1) Tính ET
        vector<int> indeg(n+1,0), ET(n+1,1);
        for(int u=1;u<=n;u++)
            for(int v: succ[u])
                indeg[v]++;
        queue<int> q;
        for(int i=1;i<=n;i++)
            if(indeg[i]==0) 
                q.push(i);

        vector<int> topo;
        while(!q.empty()){
            int u=q.front(); q.pop();
            topo.push_back(u);
            for(int v:succ[u]){
                ET[v] = max(ET[v], ET[u]+1);
                if(--indeg[v]==0)
                    q.push(v);
            }
        }
        int L = 0;
        for(int i=1;i<=n;i++) L = max(L, ET[i]);

        // 2) Tính chuỗi từ u tới sink để lấy LT
        vector<int> outdeg(n+1,0), CP(n+1,1);
        for(int u=1;u<=n;u++)
            for(int v: succ[u])
                outdeg[u]++;
        queue<int> qr;
        for(int i=1;i<=n;i++)
            if(outdeg[i]==0)
                qr.push(i);

        while(!qr.empty()){
            int u=qr.front(); qr.pop();
            for(int v: pred[u]){
                CP[v] = max(CP[v], CP[u]+1);
                if(--outdeg[v]==0)
                    qr.push(v);
            }
        }
        vector<int> LT(n+1);
        for(int i=1;i<=n;i++)
            LT[i] = L - CP[i] + 1;

        // 3) Binary search k
        int lo = (n+L-1)/L, hi = n, best = n;
        while(lo<=hi){
            int mid = (lo+hi)/2;
            // Dựng flow
            int S=0, Tnode = 1 + n + L + 1;
            MaxFlow mf(Tnode+1);
            // S -> tasks
            for(int i=1;i<=n;i++){
                mf.addEdge(S, i, 1);
                // task i -> slot t
                for(int t=ET[i]; t<=LT[i]; t++){
                    mf.addEdge(i, n+t, 1);
                }
            }
            // slots -> Tnode
            for(int t=1;t<=L;t++){
                mf.addEdge(n+t, Tnode, mid);
            }
            int flow = mf.maxflow(S, Tnode);
            if(flow==n){
                best = mid;
                hi = mid-1;
            } else {
                lo = mid+1;
            }
        }

        cout<<L<<" "<<best<<"\n";
    }
    return 0;
}
