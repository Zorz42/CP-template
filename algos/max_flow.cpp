struct MaxFlow{
	int n;
	vc<vi>adj;
	vc<vl>cp;

	MaxFlow(int n):n(n){
		adj=vc<vc<int>>(n);
		cp=vc(n,vc(n,0LL));
	}

	// connect a and b with capacity c
	void add(int a,int b,int c){
		if(cp[a][b]==0){
			adj[a].pb(b);
			adj[b].pb(a);
		}
		cp[a][b]+=c;
	}

	ll bfs(int s,int t,vi&p){
		fill(all(p),-1);
		p[s]=-2;
		queue<pii>q;
		q.push({s,1e9});
		while(!q.empty()){
			int c=q.front().f1;
			ll f=q.front().f2;
			q.pop();
			for(int x:adj[c]){
				if(p[x]==-1&&cp[c][x]){
					p[x]=c;
					ll r=min(f,cp[c][x]);
					if(x==t)
						return r;
					q.push({x,r});
				}
			}
		}
		return 0;
	}

	// call only once
	ll maxflow(int s,int t){
		ll f=0,r;
		vi pr(n);
		while((r=bfs(s,t,pr))){
			f+=r;
			int cu=t;
			while(cu!=s){
				int p=pr[cu];
				cp[p][cu]-=r;
				cp[cu][p]+=r;
				cu=p;
			}
		}
		return f;
	}
};
