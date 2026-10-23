struct MaxFlow{
	struct E{int to;ll c;};
	vc<E>e;vc<vi>g;vi d,it;
	MaxFlow(int n):g(n),d(n),it(n){}
	// connect a and b with capacity c
	void add(int a,int b,ll c){
		g[a].pb(sz(e));e.pb({b,c});
		g[b].pb(sz(e));e.pb({a,0});
	}
	ll dfs(int u,int t,ll f){
		if(u==t||!f)return f;
		ll r=0;
		for(int&i=it[u];i<sz(g[u]);i++){
			E&x=e[g[u][i]];
			if(d[x.to]==d[u]+1)if(ll p=dfs(x.to,t,min(f-r,x.c))){
				x.c-=p;e[g[u][i]^1].c+=p;
				if((r+=p)==f)return r;
			}
		}
		return r;
	}
	// call only once
	ll maxflow(int s,int t){
		ll f=0;
		while(1){
			fill(all(d),-1);fill(all(it),0);
			d[s]=0;queue<int>q;q.push(s);
			while(sz(q)){
				int u=q.front();q.pop();
				for(int i:g[u])if(e[i].c&&d[e[i].to]<0)d[e[i].to]=d[u]+1,q.push(e[i].to);
			}
			if(d[t]<0)return f;
			f+=dfs(s,t,LLONG_MAX);
		}
	}
};
