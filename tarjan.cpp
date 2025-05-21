int N, M, timer, tin[maxN], low[maxN];
bool vis[maxN];
vector<int> G[maxN];
vector<pii> bridges;

void dfs(int u = 1, int p = 0){
    vis[u] = true;
    tin[u] = low[u] = ++timer;
    for(int v : G[u]){
        if(v != p){
            if(vis[v])  low[u] = min(low[u], tin[v]);
            else {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if(low[v] > tin[u])
                    bridges.push_back({u, v});
            }
        }
    }
}
