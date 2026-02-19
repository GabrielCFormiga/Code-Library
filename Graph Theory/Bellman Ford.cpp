// Bellman-Ford
//
// Encontra o menor caminho de um ponto a outro de um grafo
// que pode conter arestas negativas.

// V - Número de vértices
// E - Número de arestas
// O(V*E)

#define INF 0x3f3f3f3f

struct Edge {
    int src, dest, weight;
};

int V, E;
vector<Edge> edges(E);
vector<int> dist(V, INF);

int bellmanFord(int src, int dest) {
    dist[src] = 0;
    vector<int> prnt(V, -1);

    // Relaxa os vértices |V-1| vezes para garantir a menor distância.
    for (int i = 0; i < V - 1; i++) {
        for (const auto& [u, v, wei] : edges) {            
            if (dist[u] != INF && dist[u] + wei < dist[v]) {
                dist[v] = dist[u] + wei;
                prnt[v] = u;
            }
        }
    }

    return dist[dest];
}

// Vê se existe um ciclo no grafo.
// Retorna um vetor vazio se não houver ciclo negativo
// ou um vetor com os vértices do ciclo caso exista
vector<int> findNegativeCycle() {
    vector<int> prnt(V, -1);  // Para rastrear o predecessor de cada vértice
    dist[0] = 0;  // Pode começar de qualquer ponto (nesse caso 0).

    for (int i = 0; i < V - 1; i++) {
        for (const auto& [u, v, wei] : edges) {         
            if (dist[u] != INF && dist[u] + wei < dist[v]) {
                dist[v] = dist[u] + wei;
                prnt[v] = u;
            }
        }
    }

    // Depois de relaxar |V-1| vezes, tentar relaxar mais 
    // uma vez para encontrar o ciclo.
    int cycleVertex = -1;
    for (const auto& [u, v, wei] : edges) {    
        if (dist[u] != INF && dist[u] + wei < dist[v]) {
            cycleVertex = v;
            break;
        }
    }

    if (cycleVertex == -1)
        return {-1};  // Não há ciclo negativo
    
        
    // Para garantir que chegamos em um vértice do ciclo, andamos V passos
    for (int i = 0; i < V; i++)
        cycleVertex = prnt[cycleVertex];
        
    vector<int> cycle;
    for (int u = cycleVertex;; u = prnt[u]) {
        cycle.push_back(u);
        if (u == cycleVertex && cycle.size() > 1)
            break;
    }
    reverse(cycle.begin(), cycle.end());
    
    return cycle;
}