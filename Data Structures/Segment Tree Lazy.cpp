// SegTree Lazy
//

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
    ll val = 0;
    Node() = default;
    Node(ll val) : val(val) {}
    Node operator+(const Node &rhs) const { return Node(val + rhs.val); }
};

struct SegTree {
    int n;
    vector<Node> t;
    vector<ll> lazy;

    SegTree(int n) : n(n), t(4 * n), lazy(4 * n, 0) {}
    SegTree(const vector<ll> &a) : SegTree(a.size()) {
        build(1, 0, n - 1, a);
    }

    void build(int pos, int tl, int tr, const vector<ll> &a) {
        if (tl == tr) { t[pos] = Node(a[tl]); return; }
        int tm = (tl + tr) / 2;
        build(2 * pos, tl, tm, a);
        build(2 * pos + 1, tm + 1, tr, a);
        t[pos] = t[2 * pos] + t[2 * pos + 1];
    }

    void apply(int pos, int tl, int tr, ll add) {
        t[pos].val += add * (tr - tl + 1);
        // p/ min/max: t[pos].val += add
        lazy[pos]  += add;
    }

    void push(int pos, int tl, int tr) {
        if (lazy[pos] != 0) {
            int tm = (tl + tr) / 2;
            apply(2 * pos, tl, tm, lazy[pos]);
            apply(2 * pos + 1, tm + 1, tr, lazy[pos]);
            lazy[pos] = 0;
        }
    }

    void update(int l, int r, ll add, int pos, int tl, int tr) {
        if (tr < l || r < tl) return;
        if (l <= tl && tr <= r) { apply(pos, tl, tr, add); return; }
        push(pos, tl, tr);
        int tm = (tl + tr) / 2;
        update(l, r, add, 2 * pos, tl, tm);
        update(l, r, add, 2 * pos + 1, tm + 1, tr);
        t[pos] = t[2 * pos] + t[2 * pos + 1];
    }
    void update(int l, int r, ll add) { update(l, r, add, 1, 0, n - 1); }

    Node query(int l, int r, int pos, int tl, int tr) {
        if (r < tl || tr < l) return Node();
        if (l <= tl && tr <= r) return t[pos];
        push(pos, tl, tr);
        int tm = (tl + tr) / 2;
        return query(l, r, 2 * pos, tl, tm) + query(l, r, 2 * pos + 1, tm + 1, tr);
    }
    Node query(int l, int r) {
        return query(l, r, 1, 0, n - 1);
    }
};
