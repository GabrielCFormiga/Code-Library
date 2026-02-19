// Mochila
//

int solve(int n, int C, vector<pair<int, int>> &v) {
	int res = 0;
	for(int mask = 1, l = 1 << n; mask < l; mask++) {
		int W = 0, V = 0;
		for(int i = 0, p = 1; i < n; i++, p <<= 1) {
			if(mask & p) {
				W += v[i].first;
				V += v[i].second;
			}
		}
		if(W <= C) {
			res = max(res, V);
		}
	}
	return res;
}
 
int main() {
	int n, C;
	cin >> n >> C;
	vector<pair<int, int>> v(n); // (w, v)
	for(int i = 0; i < n; i++) cin >> v[i].first >> v[i].second;
	cout << solve(n, C, v) << endl;
	return 0;
}