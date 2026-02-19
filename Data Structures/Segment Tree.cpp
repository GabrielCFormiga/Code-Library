// SegTree
//
// build : O(n)
// update : O(logn)
// query : O(logn)

struct node {
    int val;

    node() {
        val = 0;
        // val = elemento neutro
    }

    node(int val) : val(val) {
    }
    
    node operator + (const node &rhs) const {
        return node(val + rhs.val);
        // return node(val op rhs.val);
    }
};

struct SegTree {
    int n;
    vector<node> st;

    SegTree(){}
    SegTree(int n) : n(n) {
        st.resize(4 * n + 2);
    } 
    SegTree(vector<int> &a) {
        n = a.size();
        st.resize(4 * n + 2);
        build(1, 0, n - 1, a);
    }

    void build(int pos, int l, int r, vector<int> &a) {
        if(l == r) {
            st[pos] = node(a[l]);
            return; 
        }
        int mi = (l + r) / 2;
        build(2 * pos, l, mi, a);
        build(2 * pos + 1, mi + 1, r, a);
        st[pos] = st[2 * pos] + st[2 * pos + 1];
    }

    void update(int x, int y, int pos, int l, int r) { //void update(int x, node y, int pos, int l, int r)
        if(l == r) {
            st[pos] = node(y); //st[pos] = y;
            return;
        }
        int mi = (l + r) / 2;
        if(x <= mi) update(x, y, 2 * pos, l, mi);
        else update(x, y, 2 * pos + 1, mi + 1, r);
        st[pos] = st[2 * pos] + st[2 * pos + 1];
    }
    void update(int x, int y) { // void update(int x, node y)
        update(x, y, 1, 0, n - 1);
    }

    node query(int x, int y, int pos, int l, int r) {
        if(y < l || r < x) return node();
        if(x <= l && r <= y) return st[pos];
        int mi = (l + r) / 2;
        return query(x, y, 2 * pos, l, mi) + query(x, y, 2 * pos + 1, mi + 1, r);
    }
    node query(int x, int y) {
        return query(x, y, 1, 0, n - 1);
    }
};