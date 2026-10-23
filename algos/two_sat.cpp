// TwoSat(n): n boolean variables 0..n-1, literal x means x is true and ~x means x is false
// either(a,b): adds clause a or b
// solve(): returns whether all clauses can be satisfied, val[i] is then a valid value of variable i
struct TwoSat{
	int n,t=0,c=0;vc<vi>g;vi tin,low,comp,st,val;
	TwoSat(int n):n(n),g(2*n){}
	int id(int x){return x<0?2*~x+1:2*x;}
	void either(int a,int b){
		g[id(a)^1].pb(id(b));
		g[id(b)^1].pb(id(a));
	}
	void dfs(int u){
		tin[u]=low[u]=++t;st.pb(u);
		for(int v:g[u]){
			if(!tin[v])dfs(v),low[u]=min(low[u],low[v]);
			else if(comp[v]<0)low[u]=min(low[u],tin[v]);
		}
		if(low[u]==tin[u]){
			int v;
			do v=st.back(),st.pop_back(),comp[v]=c;while(v!=u);
			c++;
		}
	}
	bool solve(){
		tin.assign(2*n,0);low=tin;comp.assign(2*n,-1);val.resize(n);
		rep(i,2*n)if(!tin[i])dfs(i);
		rep(i,n){
			if(comp[2*i]==comp[2*i+1])return 0;
			val[i]=comp[2*i]<comp[2*i+1];
		}
		return 1;
	}
};
