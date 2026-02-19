// Floyd-Warshall
//
// encontra o menor caminho entre todo par de vertices
// returna 1 se ha ciclo negativo
//
// dist[i][i] = 0
// para i != j 
//    d[i][j] = peso , se há aresta
//    dist[i][j] = INF, c.c.
//
// O(n^3)

const long long LINF = 0x3f3f3f3f3f3f3f3fll;
int n;
long long dist[n][n];

bool floydWarshal() {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    for (int i = 0; i < n; i++) if (dist[i][i] < 0) return 1;

    return 0;
}