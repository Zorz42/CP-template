struct MinCostFlow{
	int n;
	vc<vi>adj,cst,cap;
	const int INF=1e9;

	MinCostFlow(int n):n(n){
		adj=vc(n,vi());
		cst=vc(n,vi(n,0));
		cap=vc(n,vi(n,0));
	}

	void add_edge(int from,int to,int capacity,int cost){
		adj[from].pb(to);
		adj[to].pb(from);
		cst[from][to]=cost;
		cst[to][from]=-cost;
		cap[from][to]=capacity;
	}

	void shortest_paths(int v0,vi&d,vi&p){
		d.assign(n,INF);
		d[v0]=0;
		vc<bool>inq(n,false);
		queue<int>q;
		q.push(v0);
		p.assign(n,-1);
		while(!q.empty()){
			int u=q.front();
			q.pop();
			inq[u]=false;
			for(int v:adj[u]){
				if (cap[u][v]>0&&d[v]>d[u]+cst[u][v]){
					d[v]=d[u]+cst[u][v];
					p[v]=u;
					if(!inq[v]){
						inq[v]=true;
						q.push(v);
					}
				}
			}
		}
	}

	int min_cost_flow(int K,int s,int t){
		int flow=0;
		int cost=0;
		vi d,p;
		while(flow<K){
			shortest_paths(s,d,p);
			if(d[t]==INF)
				break;
			int f=K-flow;
			int cur=t;
			while(cur!=s){
				f=min(f,cap[p[cur]][cur]);
				cur=p[cur];
			}
			flow+=f;
			cost+=f*d[t];
			cur=t;
			while(cur!=s){
				cap[p[cur]][cur]-=f;
				cap[cur][p[cur]]+=f;
				cur=p[cur];
			}
		}
		return flow<K?-1:cost;
	}
};
