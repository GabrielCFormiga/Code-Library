// SegTree Lazy
//

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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
    vector<ll> lazy;

    SegTree(int n) : n(n) {
        t.assign(4 * n, node());
        lazy.assign(4 * n, 0);
    }

    SegTree(vector<int> &a) {
        n = a.size();
        t.assign(4 * n, node());
        lazy.assign(4 * n, 0);
        build(1, 0, n - 1, a);
    }

    void unlazy(int pos, int tl, int tr) {
        if (lazy[pos] != 0) {
            t[pos].val = t[pos].val + lazy[pos] * (tr - tl + 1);
            if (tl != tr) {
                lazy[2 * pos] = lazy[2 * pos] + lazy[pos];
                lazy[2 * pos + 1] = lazy[2 * pos + 1] + lazy[pos];
            }
            lazy[pos] = 0;
        }
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

    void update(int l, int r, int add, int pos, int tl, int tr) {
        unlazy(pos, tl, tr);
        if (tr < l || r < tl) return;
        if (l <= tl && tr <= r) {
            lazy[pos] = add;
            unlazy(pos, tl, tr);
            return;
        }
        int tm = (tl + tr) / 2;
        update(l, r, add, 2 * pos, tl, tm);
        update(l, r, add, 2 * pos + 1, tm + 1, tr);
        t[pos] = t[2 * pos] + t[2 * pos + 1];
    }
    void update(int l, int r, int add) { 
        update(l, r, add, 1, 0, n - 1);
    }

    node query(int l, int r, int pos, int tl, int tr) {
        unlazy(pos, tl, tr);
        if(r < tl || tr < l) return node();
        if(l <= tl && tr <= r) return t[pos];
        int tm = (tl + tr) / 2;
        return query(l, r, 2 * pos, tl, tm) + query(l, r, 2 * pos + 1, tm + 1, tr);
    }
    node query(int l, int r) {
        return query(l, r, 1, 0, n - 1);
    }
};
