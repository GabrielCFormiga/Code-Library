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

    void build(int pos, int tl, int tr, vector<int> &a) {
        if(tl == tr) {
            t[pos] = node(a[tl]);
            return; 
        }
        int tm = (tl + tr) / 2;
        build(2 * pos, tl, tm, a);
        build(2 * pos + 1, tm + 1, tr, a);
        t[pos] = t[2 * pos] + t[2 * pos + 1];
    }

    void update(int i, int new_val, int pos, int tl, int tr) {
        if(tl == tr) {
            t[pos] = node(new_val);
            return;
        }
        int tm = (tl + tr) / 2;
        if(i <= tm) update(i, new_val, 2 * pos, tl, tm);
        else update(i, new_val, 2 * pos + 1, tm + 1, tr);
        t[pos] = t[2 * pos] + t[2 * pos + 1];
    }
    void update(int i, int new_val) { 
        update(i, new_val, 1, 0, n - 1);
    }

    node query(int l, int r, int pos, int tl, int tr) {
        if(r < tl || tr < l) return node();
        if(l <= tl && tr <= r) return t[pos];
        int tm = (tl + tr) / 2;
        return query(l, r, 2 * pos, tl, tm) + query(l, r, 2 * pos + 1, tm + 1, tr);
    }
    node query(int l, int r) {
        return query(l, r, 1, 0, n - 1);
    }
};
