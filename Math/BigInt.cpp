// Big int
//
// https://vjudge.net/problem/UVA-10106 - 10^250

int main() {

    string x, y;
    cin >> x >> y;

    int n = x.size(), m = y.size();
    vector<int> a(n), b(m), p(n + m, 0);

    // invertendo para facilitar a lógica
    for (int i = 0; i < n; i++) a[i] = x[n - 1 - i] - '0';
    for (int j = 0; j < m; j++) b[j] = y[m - 1 - j] - '0';

    // Multiplicação O(n·m)
    for (int i = 0; i < n; i++) {
        int carry = 0;
        for (int j = 0; j < m; j++) {
            int idx = i + j;
            int prod = a[i] * b[j] + p[idx] + carry;
            p[idx] = prod % 10;
            carry = prod / 10;
        }
        // adiciona o carry
        p[i + m] += carry;
    }

    // Remove zeros à esquerda (do fim do vetor invertido)
    int k = n + m - 1;
    while (k > 0 && p[k] == 0) --k;

    // Imprime resultado em ordem correta
    for (int i = k; i >= 0; i--) {
        cout << p[i];
    }
    cout << "\n";
}
