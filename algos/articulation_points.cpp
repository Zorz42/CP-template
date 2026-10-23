// Articulation(n): undirected graph on nodes 0..n-1
// add(a,b): edge between a and b
// get(): all articulation points (nodes whose removal disconnects their component) in increasing order
struct Articulation{
	int t=0;vc<vi>g;vi tin,low,cut;
	Articulation(int n):g(n),tin(n),low(n),cut(n){}
	void add(int a,int b){
		g[a].pb(b);
		g[b].pb(a);
	}
	void dfs(int u,int p){
		tin[u]=low[u]=++t;
		int ch=0;
		for(int v:g[u])if(v!=p){
			if(tin[v])low[u]=min(low[u],tin[v]);
			else{
				dfs(v,u);
				low[u]=min(low[u],low[v]);
				if(low[v]>=tin[u]&&p>=0)cut[u]=1;
				ch++;
			}
		}
		if(p<0&&ch>1)cut[u]=1;
	}
	vi get(){
		rep(i,sz(g))if(!tin[i])dfs(i,-1);
		vi r;
		rep(i,sz(g))if(cut[i])r.pb(i);
		return r;
	}
};
