// BFS
// 
// Encontra o menor caminho de um ponto a outro.
// Parecido com o Dijkstra porem mais eficiente
// já que cada aresta só tem peso 0 ou 1.

// O(n)

#define INF 0x3f3f3f3f

vector<vector<pair<int,int>>> adj;

int bfs_01(int n, int s) {
    vector<int> dist(n, INF);
    dist[s] = 0;

    deque<int> q;
    q.push_front(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        for (const auto& [v,w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 1)
                    q.push_back(v);
                else
                    q.push_front(v);
            }
        }
    }

    return dist[n-1];
}