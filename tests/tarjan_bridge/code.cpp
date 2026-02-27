// cses: necessary roads

// HEAD

const int maxN=100000;

// ALGO

void solve(){
	int n,m;
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int a,b;
		cin>>a>>b;
		a--;b--;
		nodes[a].pb(b);
		nodes[b].pb(a);
	}
	tarjan_bridge(0,0);
	sort(all(bridges));
	cout<<bridges.size()<<"\n";
	for(auto[i,j]:bridges)
		cout<<i+1<<" "<<j+1<<"\n";
}

int main(){
    ios::sync_with_stdio(false);cout.tie(0);cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solve();
    return 0;
}
