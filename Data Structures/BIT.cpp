// BIT
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
			t[i] += a[i - 1];
			int r = i + (i & -i);
			if (r <= n) t[r] += t[i];
		}
	}

	ll query(int r) {
		ll ret = 0;
		for (++r; r > 0; r -= r & -r) ret += t[r];
		return ret;
	}
	ll query(int l, int r) {
		return query(r) - query(l - 1);
	}

	void update(int i, ll add) {
		for (++i; i <= n; i += i & -i) t[i] += add;
	}
};