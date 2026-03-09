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

template <typename T>
struct CoordinateCompression {
    vector<T> d;

    CoordinateCompression(const vector<T> &vec) {
        d = vec;
        sort(d.begin(), d.end());
        d.erase(unique(d.begin(), d.end()), d.end());
    }

    int get_id(T x) {
        return lower_bound(d.begin(), d.end(), x) - d.begin();
    }

    T get_value(int id) {
        return d[id];
    }
};
