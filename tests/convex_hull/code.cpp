// cses: convex hull

// HEAD

// ALGO

void solve(){
	int n;
	cin>>n;
	vc<pt>a(n);
	for(auto&[x,y]:a)
		cin>>x>>y;
	convex_hull(a,1);
	sort(all(a));
	cout<<sz(a)<<"\n";
	for(auto[x,y]:a)
		cout<<x<<" "<<y<<"\n";
}

int main(){
    ios::sync_with_stdio(false);cout.tie(0);cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solve();
    return 0;
}
