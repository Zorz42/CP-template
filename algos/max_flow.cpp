struct MaxFlow{
	int n;
	vector<vector<int>>adj;
	vector<vector<ll>>cp;

	MaxFlow(int n):n(n){
		adj=vector<vector<int>>(n);
		cp=vector(n,vector(n,0LL));
	}

	// connect a and b with capacity c
	void add(int a,int b,int c){
		if(cp[a][b]==0){
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		cp[a][b]+=c;
	}

	ll bfs(int s,int t,vector<int>&p){
		fill(p.begin(),p.end(),-1);
		p[s]=-2;
		queue<pair<int,int>>q;
		q.push({s,1e9});
		while(!q.empty()){
			int c=q.front().first;
			ll f=q.front().second;
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
		vector<int>pr(n);
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
