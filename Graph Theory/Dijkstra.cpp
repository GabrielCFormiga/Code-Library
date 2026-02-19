// Dijkstra
//
// Encontra o menor caminho do vértice de index s até os outros vértices
//
// O(n log(n))

const int INF = 0x3f3f3f3f;
vector<vector<pair<int, int>>> adj; // {to, weight}

int dijkstra(int n, int s) {
    vector<int> dist(n, INF);

    // origem
    dist[s] = 0;

    using pi = pair<int,int>;
    priority_queue<pi, vector<pi>, greater<pi>> q;
    q.emplace(0,s);
    while (!q.empty()) {
        auto [w,u] = q.top();
        q.pop();

        if (u == n-1) break;
        if (w != dist[u]) continue;

        for (auto [W,v] : adj[u]) {
            if (w+W < dist[v]) {
                dist[v] = w+W;
                q.emplace(w+W,v);
            }
        }
    }

    return dist[n-1];
}