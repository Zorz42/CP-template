// cses: giant pizza

// HEAD

// ALGO

void solve(){
	int n,m;
	cin>>n>>m;
	TwoSat ts(m);
	vc<pii>w(n);
	for(auto&[a,b]:w){
		char ca,cb;
		cin>>ca>>a>>cb>>b;
		a=ca=='+'?a-1:~(a-1);
		b=cb=='+'?b-1:~(b-1);
		ts.either(a,b);
	}
	if(!ts.solve()){
		cout<<"IMPOSSIBLE\n";
		return;
	}
	auto ok=[&](int x){return x<0?!ts.val[~x]:ts.val[x];};
	for(auto[a,b]:w)
		if(!ok(a)&&!ok(b)){
			cout<<"WRONG\n";
			return;
		}
	rep(i,m)
		cout<<(ts.val[i]?"+ ":"- ");
	cout<<"\n";
}

int main(){
    ios::sync_with_stdio(false);cout.tie(0);cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solve();
    return 0;
}
