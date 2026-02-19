// Manacher's Algorithm
//
// Encontra todos os sub-palindromos de uma string em tempo linear

// O(n)

vector<int> manacher(string& s) {
    string t = "#";
    for (char c : s) {
        t.pb(c);
        t += "#";
    }

    int n = t.size();
    t = "$" + t + "^";

    vector<int> p(n + 2);
    int l = 0, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = min(r - i, p[l + r - i]);

        while(t[i - p[i]] == t[i + p[i]])
            p[i]++;

        if (i + p[i] > r) {
            l = i - p[i];
            r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}