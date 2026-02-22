// Sparse Table
//

template <typename T>
struct SparseTable {
    vector<vector<T>> st;
    int n, k; // k = 24 is enough for n <= 10^7

    T op(T a, T b) { 
        return std::min(a, b); 
    }

    SparseTable(const vector<T> &vec) {
        n = vec.size();
        k = __lg(n) + 1;
        st.assign(k + 1, vector<T>(n));
        for (int j = 0; j < n; j++) st[0][j] = vec[j];
        for (int i = 1; i <= k; i++) 
            for (int j = 0; j + (1 << i) <= n; j++) 
                st[i][j] = op(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }

    T query(int l, int r) {
        int i = __lg(r - l + 1);
        return op(st[i][l], st[i][r - (1 << i) + 1]);
    }
};