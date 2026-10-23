// HEAD

// ALGO

istream&operator>>(istream&s,pt&p){return s>>p.x>>p.y;}

poly read_poly(){
	int n;
	cin>>n;
	poly g(n);
	for(pt&p:g)
		cin>>p;
	return g;
}

template<class F>void read(F f){
	string t;
	cin>>t;
	pt a,b;
	if(t=="pt")cin>>a,f(a);
	if(t=="line")cin>>a>>b,f(line{a,b});
	if(t=="seg")cin>>a>>b,f(seg{a,b});
	if(t=="poly")f(read_poly());
}

void solve(){
	int q;
	cin>>q;
	const char*where[]={"OUTSIDE","BOUNDARY","INSIDE"};
	while(q--){
		string t;
		cin>>t;
		if(t=="inside"){
			poly g=read_poly();
			pt p;
			cin>>p;
			cout<<where[inside(g,p)]<<"\n";
		}else read([&](auto a){
			read([&](auto b){
				cout<<(intersect(a,b)?"YES":"NO")<<"\n";
			});
		});
	}
}

int main(){
    ios::sync_with_stdio(false);cout.tie(0);cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solve();
    return 0;
}
