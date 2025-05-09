#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const double PI = acos(-1.0);

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("garden.inp", "r", stdin);
    freopen("garden.out", "w", stdout);
    int n;
    if(!(cin >> n)) return 0;
    vector<pair<int,int>> diagonals;
    diagonals.reserve(n-3);
    for(int i=0,u,v;i<n-3;i++){
        cin >> u >> v;
        diagonals.emplace_back(u, v);
    }

    // 1) Tính bán kính R sao cho diện tích đa giác đều = 1:
    //    A = n * R^2 * sin(2π/n) / 2 = 1  =>  R = sqrt(2/(n * sin(2π/n)))
    double R = sqrt(2.0 / (n * sin(2*PI/n)));

    // 2) Tạo toạ độ các đỉnh:
    vector<double> X(n), Y(n);
    for(int i=0;i<n;i++){
        double ang = 2*PI*i/n;
        X[i] = R * cos(ang);
        Y[i] = R * sin(ang);
    }

    // 3) Tập hợp các cạnh (polygon biên + diagonals)
    unordered_set<ll> edge_set;
    edge_set.reserve(2*(n + diagonals.size()));
    auto key = [&](int u, int v){
        if(u>v) swap(u,v);
        return ll(u)*n + v;
    };
    // biên
    for(int i=0;i<n;i++){
        int j = (i+1)%n;
        edge_set.insert(key(i,j));
    }
    // diagonals
    for(auto &d: diagonals){
        edge_set.insert(key(d.first, d.second));
    }

    // 4) Xây dựng danh sách kề cho mỗi đỉnh
    vector<vector<int>> adj(n);
    for(int i=0;i<n;i++){
        int j = (i+1)%n;
        adj[i].push_back(j);
        adj[j].push_back(i);
    }
    for(auto &d: diagonals){
        int u=d.first, v=d.second;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 5) Với mỗi đỉnh v, sort neighbors theo góc quanh v
    for(int v=0;v<n;v++){
        auto &nei = adj[v];
        sort(nei.begin(), nei.end(), [&](int a, int b){
            int da = (a - v + n) % n;
            int db = (b - v + n) % n;
            return da < db;
        });
    }

    // 6) Tìm các tam giác (face) nội bộ: với mỗi v, mỗi cặp lân cận (u,w) nếu (u,w) thuộc E thì tạo tam giác (v,u,w)
    int expected = n-2;
    vector<array<int,3>> tris;
    tris.reserve(expected);
    unordered_set<string> seen;
    seen.reserve(expected*2);

    auto tri_key = [&](int a,int b,int c){
        array<int,3> t = {a,b,c};
        sort(t.begin(), t.end());
        return to_string(t[0])+"_"+to_string(t[1])+"_"+to_string(t[2]);
    };

    for(int v=0;v<n;v++){
        auto &nei = adj[v];
        int m = nei.size();
        for(int i=0;i<m;i++){
            int u = nei[i];
            int w = nei[(i+1)%m];
            // kiểm tra có cạnh u-w không?
            if(edge_set.count(key(u,w))){
                // tính diện tích tam giác (v,u,w)
                double area = fabs(
                    (X[u]-X[v])*(Y[w]-Y[v]) 
                  - (X[w]-X[v])*(Y[u]-Y[v])
                ) * 0.5;
                if(area > 1e-15){
                    string k = tri_key(v,u,w);
                    if(seen.insert(k).second){
                        array<int,3> t = {v,u,w};
                        tris.push_back(t);
                    }
                }
            }
        }
    }

    // 7) Gán chỉ số cho mỗi tam giác, tính trọng số = diện tích
    int T = tris.size(); // phải là n-2
    vector<double> weight(T);
    for(int i=0;i<T;i++){
        auto &t = tris[i];
        double area = fabs(
            (X[t[1]]-X[t[0]])*(Y[t[2]]-Y[t[0]]) 
          - (X[t[2]]-X[t[0]])*(Y[t[1]]-Y[t[0]])
        ) * 0.5;
        weight[i] = area;
    }

    // 8) Xây dựng cây đối ngẫu: hai tam giác kề nhau nếu chia sẻ một diagonal
    //    Map từ mỗi diagonal edge -> 1 hoặc 2 tam giác chứa nó
    unordered_map<ll, pair<int,int>> edge2tri;
    edge2tri.reserve((n-3)*2);
    vector<vector<int>> tree(T);
    for(int i=0;i<T;i++){
        auto &t = tris[i];
        // xét 3 cạnh
        for(int k=0;k<3;k++){
            int u = t[k], v = t[(k+1)%3];
            ll ek = key(u,v);
            // chỉ quan tâm diagonal (có trong diagonals, tức edge_set nhưng không phải biên)
            if(!((v == (u+1)%n) || (u == (v+1)%n))){ 
                // là diagonal
                auto &pr = edge2tri[ek];
                if(pr.first==0 && pr.second==0){
                    pr.first = i+1; // đánh dấu index+1
                } else {
                    pr.second = i+1;
                }
            }
        }
    }
    // kết nối hai tam giác qua mỗi diagonal
    for(auto &it: edge2tri){
        int a = it.second.first -1;
        int b = it.second.second -1;
        if(a>=0 && b>=0){
            tree[a].push_back(b);
            tree[b].push_back(a);
        }
    }

    // 9) DP trên cây: dp[u][0]=max weight con subtree u khi u không lấy
    //                  dp[u][1]=max khi u lấy
    vector<array<double,2>> dp(T, {0,0});
    vector<int> parent(T, -1), order; order.reserve(T);
    // duyệt BFS để lấy thứ tự ngược (post-order)
    order.push_back(0);
    for(int i=0;i<(int)order.size();i++){
        int u = order[i];
        for(int v: tree[u]){
            if(v==parent[u]) continue;
            parent[v] = u;
            order.push_back(v);
        }
    }
    // post-order tính dp
    for(int idx=T-1; idx>=0; idx--){
        int u = order[idx];
        dp[u][1] = weight[u];
        dp[u][0] = 0;
        for(int v: tree[u]){
            if(v==parent[u]) continue;
            dp[u][0] += max(dp[v][0], dp[v][1]);
            dp[u][1] += dp[v][0];
        }
    }

    double ans = max(dp[0][0], dp[0][1]);
    cout << fixed << setprecision(6) << ans << "\n";
    return 0;
}
