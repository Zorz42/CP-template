// cses: string matching

// HEAD

// ALGO

void solve(){
	string a,b;
	cin>>a>>b;
	FastString fa(b+a);
	int r=0;
	rep(i,sz(a)-sz(b)+1)
		r+=fa.get(0,sz(b))==fa.get(i+sz(b),i+2*sz(b));
	cout<<r<<"\n";
}

int main(){
    ios::sync_with_stdio(false);cout.tie(0);cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solve();
    return 0;
}
