// cses: distinct substrings

// HEAD

// ALGO

void solve(){
	string s;
	cin>>s;
	vi p=suffix_array(s),l=lcp(s,p);
	ll n=sz(s),r=n*(n+1)/2;
	for(int x:l)
		r-=x;
	cout<<r<<"\n";
}

int main(){
    ios::sync_with_stdio(false);cout.tie(0);cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solve();
    return 0;
}
