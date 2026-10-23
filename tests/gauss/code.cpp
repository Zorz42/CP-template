// cses: system of linear equations

// HEAD

// ALGO

void solve(){
	const ll p=1e9+7;
	int n,m;
	cin>>n>>m;
	vc<vl>a(n,vl(m+1));
	for(vl&r:a)
		for(ll&v:r)
			cin>>v;
	vl x=gauss(a,p);
	if(x.empty()){
		cout<<"-1\n";
		return;
	}
	for(vl&r:a){
		ll s=0;
		rep(j,m)
			s=(s+r[j]*x[j])%p;
		if(s!=r[m]){
			cout<<"WRONG\n";
			return;
		}
	}
	for(ll v:x)
		cout<<v<<" ";
	cout<<"\n";
}

int main(){
    ios::sync_with_stdio(false);cout.tie(0);cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solve();
    return 0;
}
