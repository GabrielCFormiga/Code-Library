// Quantidade de Ciclos
//
// https://atcoder.jp/contests/abc399/tasks/abc399_c

void dfs(int v, int parent){
    if (!vis[v]) vis[v] = true;

    for (auto w : g[v]){
        if (!vis[w]){
            dfs(w, v);
        }
        else if (w != parent) ans++;
    }
}   

int main(){
    for (int i = 0; i < n; i++){
        if (!vis[i]) {
            dfs(i, -1);
        }
    }
    
    cout << ans/2 << "\n";
}