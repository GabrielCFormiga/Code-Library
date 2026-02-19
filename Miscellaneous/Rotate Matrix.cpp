// Invertendo Matrizes 90º
//
// 90 graus anti-horario

void rotateMatrix(vector<vector<int>>& mat, int N) {
    for (int x = 0; x < N / 2; x++) {
        for (int y = x; y < N - x - 1; y++) {
            int temp = mat[x][y];

            // direita → topo
            mat[x][y] = mat[y][N - 1 - x];

            // fundo → direita
            mat[y][N - 1 - x] = mat[N - 1 - x][N - 1 - y];

            // esquerda → fundo
            mat[N - 1 - x][N - 1 - y] = mat[N - 1 - y][x];

            // topo (temp) → esquerda
            mat[N - 1 - y][x] = temp;
        }
    }
}

// 90 graus horario (ou 3x anti-horario)

void rotateMatrixCW(vector<vector<int>>& mat, int N) {
    for (int x = 0; x < N / 2; x++) {
        for (int y = x; y < N - x - 1; y++) {
            int temp = mat[x][y];

            // esquerda → topo
            mat[x][y] = mat[N - 1 - y][x];

            // fundo → esquerda
            mat[N - 1 - y][x] = mat[N - 1 - x][N - 1 - y];

            // direita → fundo
            mat[N - 1 - x][N - 1 - y] = mat[y][N - 1 - x];

            // topo (temp) → direita
            mat[y][N - 1 - x] = temp;
        }
    }
}