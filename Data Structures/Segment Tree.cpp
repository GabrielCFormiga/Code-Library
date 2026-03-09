// SegTree
//

struct node {
    ll val;
    node() {
        val = 0;
    }
    node(ll val) : val(val) {
    }
    node operator + (const node &rhs) const {
        return node(val + rhs.val);
        // return node(val op rhs.val);
    }
};

struct SegTree {
    int n;
    vector<node> t;

    SegTree(int n) : n(n) {
        t.assign(4 * n, node());
    }

    SegTree(vector<int> &a) {
        n = a.size();
        t.resize(4 * n);
        build(1, 0, n - 1, a);
    }

    void build(int pos, int l, int r, vector<int> &a) {
        if(l == r) {
            t[pos] = node(a[l]);
            return; 
        }
        int m = (l + r) / 2;
        build(2 * pos, l, m, a);
        build(2 * pos + 1, m + 1, r, a);
        t[pos] = t[2 * pos] + t[2 * pos + 1];
    }

    void update(int i, int val, int pos, int l, int r) {
        if(l == r) {
            t[pos] = node(val);
            return;
        }
        int m = (l + r) / 2;
        if(i <= m) update(i, val, 2 * pos, l, m);
        else update(i, val, 2 * pos + 1, m + 1, r);
        t[pos] = t[2 * pos] + t[2 * pos + 1];
    }
    void update(int i, int val) { 
        update(i, val, 1, 0, n - 1);
    }

    node query(int i, int j, int pos, int l, int r) {
        if(j < l || r < i) return node();
        if(i <= l && r <= j) return t[pos];
        int m = (l + r) / 2;
        return query(i, j, 2 * pos, l, m) + query(i, j, 2 * pos + 1, m + 1, r);
    }
    node query(int i, int j) {
        return query(i, j, 1, 0, n - 1);
    }
};
