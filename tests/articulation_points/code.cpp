// cses: necessary cities

// HEAD

// ALGO

void solve(){
	int n,m;
	cin>>n>>m;
	Articulation g(n);
	rep(i,m){
		int a,b;
		cin>>a>>b;
		g.add(a-1,b-1);
	}
	vi r=g.get();
	cout<<sz(r)<<"\n";
	for(int x:r)
		cout<<x+1<<" ";
	cout<<"\n";
}

int main(){
    ios::sync_with_stdio(false);cout.tie(0);cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solve();
    return 0;
}
