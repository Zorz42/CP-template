struct MinCostFlow{
	struct E{int to;ll c,w;};
	int n;vc<E>e;vc<vi>g;
	MinCostFlow(int n):n(n),g(n){}
	void add_edge(int a,int b,ll cap,ll cost){
		g[a].pb(sz(e));e.pb({b,cap,cost});
		g[b].pb(sz(e));e.pb({a,0,-cost});
	}
	pll min_cost_flow(int s,int t,ll K=LLONG_MAX){
		ll f=0,c=0;
		while(f<K){
			vl d(n,LLONG_MAX);vi p(n),inq(n);
			queue<int>q;q.push(s);d[s]=0;
			while(sz(q)){
				int u=q.front();q.pop();inq[u]=0;
				for(int i:g[u]){
					E&x=e[i];
					if(x.c&&d[u]+x.w<d[x.to]){
						d[x.to]=d[u]+x.w;p[x.to]=i;
						if(!inq[x.to])inq[x.to]=1,q.push(x.to);
					}
				}
			}
			if(d[t]==LLONG_MAX)break;
			ll r=K-f;
			for(int v=t;v!=s;v=e[p[v]^1].to)r=min(r,e[p[v]].c);
			for(int v=t;v!=s;v=e[p[v]^1].to)e[p[v]].c-=r,e[p[v]^1].c+=r;
			f+=r;c+=r*d[t];
		}
		return{f,c};
	}
};
