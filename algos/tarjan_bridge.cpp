int timer,tin[maxN],low[maxN];
bool vis[maxN];
vi nodes[maxN];
vector<pii>bridges;

void tarjan_bridge(int u=0,int p=0){
	vis[u]=true;
	tin[u]=low[u]=++timer;
	for(int v:nodes[u]){
		if(v!=p){
			if(vis[v])  
				low[u]=min(low[u],tin[v]);
			else{
				tarjan_bridge(v,u);
				low[u]=min(low[u],low[v]);
				if(low[v]>tin[u])
					bridges.push_back({u,v});
			}
		}
	}
}
