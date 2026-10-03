// Strongly Connected Components (Kosaraju)
//
// Encontra as componentes fortemente conexas de um grafo direcionado
// run() retorna comp, onde comp[u] é o id da componente de u
//
// Os ids seguem a ordem topológica do grafo condensado:
// se existe aresta comp[u] -> comp[v] (com comp[u] != comp[v]), então comp[u] < comp[v]
//
// V = {0, 1, 2, ..., N - 1}
// O(N + M) : M = |E|, N = |V|

struct SCC {
    int n;
    vector<vector<int>> adj, inv;

    SCC(int n): n(n), adj(n), inv(n) {}

    void add_edge(int a, int b) {
        adj[a].push_back(b);
        inv[b].push_back(a);
    }

    void dfs1(vector<int>& vis, vector<int>& topo, int u) {
        vis[u] = true;
        for (auto v : adj[u]) {
            if (vis[v]) continue;
            dfs1(vis, topo, v);
        }
        topo.push_back(u);
    }

    void dfs2(vector<int>& comp, int c, int u) {
        comp[u] = c;
        for (auto v : inv[u]) {
            if (comp[v] == -1) dfs2(comp, c, v);
        }
    }

    vector<int> run() {
        vector<int> vis(n), topo;
        for (int u = 0; u < n; u++) {
            if (vis[u]) continue;
            dfs1(vis, topo, u);
        }

        reverse(topo.begin(), topo.end());

        vector<int> comp(n, -1);
        int c = 0;
        for (auto u : topo) {
            if (comp[u] != -1) continue;
            dfs2(comp, c, u);
            c++;
        }
        return comp;
    }
};
