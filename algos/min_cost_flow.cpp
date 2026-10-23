// MinCostFlow(n): graph on nodes 0..n-1
// add_edge(a,b,cap,cost): directed edge a->b
// min_cost_flow(s,t,K): sends at most K flow from s to t as cheaply as possible, returns {flow,cost}
// negative costs are allowed if there is no negative cycle
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
		vl pi(n,LLONG_MAX);vi inq(n);
		queue<int>q;q.push(s);pi[s]=0;
		while(sz(q)){
			int u=q.front();q.pop();inq[u]=0;
			for(int i:g[u])if(e[i].c&&pi[u]+e[i].w<pi[e[i].to]){
				pi[e[i].to]=pi[u]+e[i].w;
				if(!inq[e[i].to])inq[e[i].to]=1,q.push(e[i].to);
			}
		}
		while(f<K&&pi[t]<LLONG_MAX){
			vl d(n,LLONG_MAX);vi p(n);
			priority_queue<pll,vc<pll>,greater<>>pq;pq.push({0,s});d[s]=0;
			while(sz(pq)){
				auto[du,u]=pq.top();pq.pop();
				if(du>d[u])continue;
				for(int i:g[u]){
					E&x=e[i];
					if(!x.c)continue;
					ll nd=du+x.w+pi[u]-pi[x.to];
					if(nd<d[x.to])d[x.to]=nd,p[x.to]=i,pq.push({nd,x.to});
				}
			}
			if(d[t]==LLONG_MAX)break;
			rep(v,n)if(d[v]<LLONG_MAX)pi[v]+=d[v];
			ll r=K-f;
			for(int v=t;v!=s;v=e[p[v]^1].to)r=min(r,e[p[v]].c);
			for(int v=t;v!=s;v=e[p[v]^1].to)e[p[v]].c-=r,e[p[v]^1].c+=r;
			f+=r;c+=r*pi[t];
		}
		return{f,c};
	}
};
