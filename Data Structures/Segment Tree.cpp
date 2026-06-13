// SegTree
//

struct Node {
    ll val = 0;
    Node() = default;
    Node(ll v) : val(v) {}
    Node operator+(const Node &rhs) const { return Node(val + rhs.val); }
};

template <typename Node>
struct SegTree {
    int n;
    vector<Node> t;
    
    SegTree(int n) : n(n), t(4 * n) {}
    SegTree(const vector<ll> &a) : SegTree(a.size()) {
        build(1, 0, n - 1, a);
    }

    void build(int pos, int tl, int tr, vector<ll> &a) {
        if(tl == tr) { t[pos] = node(a[tl]); return; }
        int tm = (tl + tr) / 2;
        build(2 * pos, tl, tm, a);
        build(2 * pos + 1, tm + 1, tr, a);
        t[pos] = t[2 * pos] + t[2 * pos + 1];
    }

    void update(int i, int new_val, int pos, int tl, int tr) {
        if(tl == tr) { t[pos] = node(new_val); return; }
        int tm = (tl + tr) / 2;
        if(i <= tm) update(i, new_val, 2 * pos, tl, tm);
        else update(i, new_val, 2 * pos + 1, tm + 1, tr);
        t[pos] = t[2 * pos] + t[2 * pos + 1];
    }
    void update(int i, int new_val) { update(i, new_val, 1, 0, n - 1); }

    node query(int l, int r, int pos, int tl, int tr) {
        if(r < tl || tr < l) return node();
        if(l <= tl && tr <= r) return t[pos];
        int tm = (tl + tr) / 2;
        return query(l, r, 2 * pos, tl, tm) + query(l, r, 2 * pos + 1, tm + 1, tr);
    }
    node query(int l, int r) { return query(l, r, 1, 0, n - 1); }
};
