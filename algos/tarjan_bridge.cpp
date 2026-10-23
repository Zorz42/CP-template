// define maxN, add undirected edges to nodes[], then call tarjan_bridge(root)
// bridges then holds every bridge {u,v} of the component of root, parallel edges are handled
int timer,tin[maxN],low[maxN];
vi nodes[maxN];
vc<pii>bridges;

void tarjan_bridge(int u=0,int p=-1){
	tin[u]=low[u]=++timer;
	bool s=0;
	for(int v:nodes[u]){
		if(v==p&&!s)s=1;
		else if(tin[v])low[u]=min(low[u],tin[v]);
		else{
			tarjan_bridge(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>tin[u])bridges.pb({u,v});
		}
	}
}
