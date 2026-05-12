// BIT
//

struct BIT {
	int n;
	vector<ll> t;

	BIT(int n) : n(n) {
		t.assign(n, 0);
	}
	BIT(vector<ll> const &a) {
		n = a.size();
		t.assign(n, 0);
		for (int i = 0; i < a.size(); ++i) {
			t[i] += a[i];
			int r = i | (i + 1);
			if (r < n) t[r] += t[i];
		}
	}
	
	ll query(int r) {
		ll ret = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1) ret += t[r];
		return ret;
	}
	ll query(int l, int r) {
		return query(r) - query(l - 1);
	}

	void update(int i, ll add) {
		for (; i < n; i = i | (i + 1)) t[i] += add;
	}
};