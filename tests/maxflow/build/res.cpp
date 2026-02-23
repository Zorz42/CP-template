#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<limits.h>
#include<math.h>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<iomanip>
#include<cstring>
#include<random>
#include<cassert>
#include<sstream>
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
using namespace std;

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


void solve(){
    int n,m;
    cin>>n>>m;
    MaxFlow g(n);
    for(int i=0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        g.add(a-1,b-1,c);
    }
    cout<<g.maxflow(0,n-1)<<"\n";
}

int main(){
    ios::sync_with_stdio(false);cout.tie(0);cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solve();
    return 0;
}

/*

 */