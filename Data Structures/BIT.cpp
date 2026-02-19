// BIT
//
// build - O(n)
// update - O(log(n))
// query - O(log(n))

struct BIT {
	vector<ll> bit;
	int n;

	BIT(int n) {
		this->n = n;
		bit.assign(n, 0);
	}

	BIT(vector<ll> const &a) : BIT(a.size()) {
		for (int i = 0; i < a.size(); ++i) {
			bit[i] += a[i];
			int r = i | (i + 1);
			if (r < n) bit[r] += bit[i];
		}
	}

	ll sum(int r) {
		ll ret = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1)
			ret += bit[r];
		return ret;
	}

	ll sum(int l, int r) {
		return sum(r) - sum(l - 1);
	}

	void add(int idx, ll delta) {
		for (; idx < n; idx = idx | (idx + 1))
			bit[idx] += delta;
	}
};