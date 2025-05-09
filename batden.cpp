#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e4 + 5;
const int MAXQ = 1e5 + 5;
const int SEG_SZ = MAXN * 4;

int N, Q;
vector<int> graph[SEG_SZ * 4], rev_graph[SEG_SZ * 4];
int seg_id = 0;  
int leaf_id[MAXN]; 


struct SegmentTree {
    int base;
    vector<vector<int>> tree;

    SegmentTree(int n, bool toLeaf) {
        base = seg_id;
        tree.resize(n * 4);
        build(1, 1, N, toLeaf);
    }

    void build(int node, int l, int r, bool toLeaf) {
        int cur_id = base + node;
        if (l == r) {
            leaf_id[l] = cur_id;
            return;
        }
        int mid = (l + r) / 2;
        int left_id = base + node * 2;
        int right_id = base + node * 2 + 1;
        build(node * 2, l, mid, toLeaf);
        build(node * 2 + 1, mid + 1, r, toLeaf);
        if (toLeaf) {
            
            graph[cur_id].push_back(left_id);
            graph[cur_id].push_back(right_id);
            rev_graph[left_id].push_back(cur_id);
            rev_graph[right_id].push_back(cur_id);
        } else {
            
            graph[left_id].push_back(cur_id);
            graph[right_id].push_back(cur_id);
            rev_graph[cur_id].push_back(left_id);
            rev_graph[cur_id].push_back(right_id);
        }
    }

    void add_edge(int node, int l, int r, int ql, int qr, int from, bool forward) {
        if (qr < l || r < ql) return;
        int cur_id = base + node;
        if (ql <= l && r <= qr) {
            if (forward) {
                graph[from].push_back(cur_id);
                rev_graph[cur_id].push_back(from);
            } else {
                graph[cur_id].push_back(from);
                rev_graph[from].push_back(cur_id);
            }
            return;
        }
        int mid = (l + r) / 2;
        add_edge(node * 2, l, mid, ql, qr, from, forward);
        add_edge(node * 2 + 1, mid + 1, r, ql, qr, from, forward);
    }
};


vector<int> order;
bool visited[SEG_SZ * 4];
int scc_id[SEG_SZ * 4], scc_count;
vector<int> scc_graph[SEG_SZ * 4];
int indegree[SEG_SZ * 4];

void dfs1(int u) {
    visited[u] = true;
    for (int v : graph[u])
        if (!visited[v])
            dfs1(v);
    order.push_back(u);
}

void dfs2(int u, int label) {
    scc_id[u] = label;
    for (int v : rev_graph[u])
        if (scc_id[v] == -1)
            dfs2(v, label);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("BATDEN.INP", "r", stdin);
    freopen("BATDEN.OUT", "w", stdout);

    cin >> N >> Q;
    seg_id = 0;

    
    SegmentTree to_tree(N, true); seg_id += N * 4;
    SegmentTree from_tree(N, false); seg_id += N * 4;

    for (int i = 0; i < Q; ++i) {
        int x, y, z, t;
        cin >> x >> y >> z >> t;

        
        for (int p = x; p <= y; ++p)
            from_tree.add_edge(1, 1, N, z, t, leaf_id[p], true);
    }

    
    int total_nodes = seg_id;
    fill(scc_id, scc_id + total_nodes, -1);
    for (int i = 0; i < total_nodes; ++i)
        if (!visited[i]) dfs1(i);

    reverse(order.begin(), order.end());
    for (int u : order)
        if (scc_id[u] == -1)
            dfs2(u, scc_count++);

    
    for (int u = 0; u < total_nodes; ++u) {
        for (int v : graph[u]) {
            if (scc_id[u] != scc_id[v]) {
                scc_graph[scc_id[u]].push_back(scc_id[v]);
                indegree[scc_id[v]]++;
            }
        }
    }

    
    vector<bool> has_leaf(scc_count, false);
    for (int i = 1; i <= N; ++i)
        has_leaf[scc_id[leaf_id[i]]] = true;

    int result = 0;
    for (int i = 0; i < scc_count; ++i)
        if (has_leaf[i] && indegree[i] == 0)
            result++;

    cout << result << '\n';
    return 0;
}
