// Kruskal
//
// Gera e retorna uma AGM de um grafo G
// Para a árvore geradora máxima basta que peso = -peso
//
// V = {0, 1, 3, ..., N - 1}
// O (MlogM + N^2) : M = |E|, N = |V|

struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

vector<Edge> kruskal(vector<Edge> *edges, int n) {
    int cost = 0;
    vector<Edge> msp;
    vector<int> tree_id(n);
    for (int i = 0; i < n; i++) tree_id[i] = i;

    sort(edges.begin(), edges.end());

    for (Edge e : edges) {
        if (tree_id[e.u] != tree_id[e.v]) {
            cost += e.weight;
            msp.push_back(e);

            // unite
            int old_id = tree_id[e.u], new_id = tree_id[e.v];
            for (int i = 0; i < n; i++) {
                if (tree_id[i] == old_id) tree_id[i] = new_id;
            }
        }
    }
}
