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

// cses: task assignment (without construction)

// ALGO

void solve(){
	int n;
	cin>>n;
	MinCostFlow g(2*n+2);
	int s=2*n,t=s+1;
	for(int x=0;x<n;x++){
		for(int y=0;y<n;y++){
			int v;
			cin>>v;
			g.add_edge(s,x,1,0);
			g.add_edge(n+y,t,1,0);
			g.add_edge(x,n+y,1,v);
		}
	}
	cout<<g.min_cost_flow(n,s,t)<<"\n";
}

int main(){
    ios::sync_with_stdio(false);cout.tie(0);cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solve();
    return 0;
}

/*

 */
