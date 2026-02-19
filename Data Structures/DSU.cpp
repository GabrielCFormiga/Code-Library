// Disjoint Set Union
//
// Estrutura que permite combinar conjuntos e 
// dizer de qual conjunto cada elemento faz parte

// Operações:
// make_set(v) -> cria um novo conjunto com o elemento v
// union_sets(a, b) -> combina os conjuntos do qual os elementos a e b fazem parte
// find_set(v) -> retorna o elemento que representa o conjunto do qual v faz parte

// Cada operação é aproximadamente O(1)

struct DSU {
    vector<int> parent, rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    void make_set(int v) {
        parent[v] = v;
        rank[v] = 0;
    }

    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]); // Path compression
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                rank[a]++;
        }
    }
};
