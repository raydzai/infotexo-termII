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

struct Node {
    int v, mx, sz, pri;
    Node *l, *r;
    Node(int _v) : v(_v), mx(_v), sz(1), pri((rand() << 16) ^ rand()), l(NULL), r(NULL) {}
};

int sz(Node* t) { return t ? t->sz : 0; }
int mx(Node* t) { return t ? t->mx : INT_MIN; }

void upd(Node* t) {
    if (!t) return;
    t->sz = 1 + sz(t->l) + sz(t->r);
    t->mx = max(t->v, max(mx(t->l), mx(t->r)));
}

void split(Node* t, int k, Node*& l, Node*& r) {
    if (!t) { l = r = NULL; return; }
    if (sz(t->l) < k) {
        split(t->r, k - sz(t->l) - 1, t->r, r);
        l = t;
    } else {
        split(t->l, k, l, t->l);
        r = t;
    }
    upd(t);
}

Node* merge(Node* l, Node* r) {
    if (!l || !r) return l ? l : r;
    if (l->pri > r->pri) {
        l->r = merge(l->r, r);
        upd(l);
        return l;
    } else {
        r->l = merge(l, r->l);
        upd(r);
        return r;
    }
}

int findMaxPos(Node* t) {
    if (!t) return 0;
    if (mx(t->l) == t->mx) return findMaxPos(t->l);
    if (t->v == t->mx) return sz(t->l) + 1;
    int p = findMaxPos(t->r);
    if (p > 0) return sz(t->l) + 1 + p;
    return 0;
}

void collect(Node* t, vkt<int>& out) {
    if (!t) return;
    collect(t->l, out);
    out.pub(t->v);
    collect(t->r, out);
}

int main() {
    raysiucapvjppro;
    srand(time(NULL));
    offen("MEMBERS");

    int n;
    ll k;
    cin >> n >> k;
    vkt<int> a(n);
    sch(i, 0, n, 1) cin >> a[i];

    Node* root = NULL;
    sch(i, 0, n, 1) {
        root = merge(root, new Node(a[i]));
    }

    Node* ans = NULL;
    sch(_, 0, n, 1) {
        if (k <= 0) break;
        int take = (int)min<ll>(sz(root), k + 1);
        Node *t1, *t2;
        split(root, take, t1, t2);
        int pos = findMaxPos(t1);
        Node *l, *mid, *r;
        split(t1, pos - 1, l, mid);
        split(mid, 1, mid, r);
        t1 = merge(l, r);
        k -= (pos - 1);
        ans = merge(ans, mid);
        root = merge(t1, t2);
    }

    ans = merge(ans, root);

    vkt<int> out;
    collect(ans, out);
    for (int i = 0; i < (int)out.size(); i++) {
        if (i) cout << ' ';
        cout << out[i];
    }

    return 0;
}
