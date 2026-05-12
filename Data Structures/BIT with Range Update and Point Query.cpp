// BIT with Range Update and Point Query
//

struct BIT {
    int n;
    vector<ll> t;

    BIT(int n) : n(n) {
        t.assign(n + 1, 0);
    }
    BIT(vector<ll> const &a) {
        n = a.size();
        t.assign(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
			t[i] += a[i-1] - (i > 1 ? a[i-2] : 0);
			int j = i + (i & -i);
			if (j <= n) t[j] += t[i];
		}
    }

    ll query(int i) {
        ll ret = 0;
        for (++i; i > 0; i -= i & -i) ret += t[i];
        return ret;
    }

    void update(int i, ll add) {
        for (++i; i <= n; i += i & -i) t[i] += add;
    }
    void update(int l, int r, ll add) {
        update(l, add);
        update(r + 1, -add);
    }
};