// Coordinate Compression
//

template <typename T>
struct CoordinateCompression {
    int n;
    vector<int> compressed;
    vector<T> original;

    CoordinateCompression(const vector<T> &vec) {
        n = vec.size();
        original = vec;
        compressed.assign(n, 0);
        vector<pair<T, int>> pairs(n);
        for (int i = 0; i < n; ++i) {
            pairs[i] = {vec[i], i};
        }
        sort(pairs.begin(), pairs.end());
        int nxt = 0;
        for (int i = 0; i < n; ++i) {
            if(i > 0 && pairs[i-1].first != pairs[i].first) nxt++;
            compressed[pairs[i].second] = nxt;
        }
    }
};
