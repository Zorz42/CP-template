// LCT(n): set of lines on integer x in [0,n)
// add_line({k,m}): adds line y=k*x+m, get(x): minimum of all lines at x (1e18 if there are none)
struct LCT{
	int n;
	vc<pll>t;
	LCT(int n):n(n),t(4*n,{0,(ll)1e18}){}
	ll ev(pll a,ll x){return a.f1*x+a.f2;}
	void add_line(pll w,int v=1,int l=0,int r=0){
		if(!r)r=n;
		int m=(l+r)/2;
		bool L=ev(w,l)<ev(t[v],l),M=ev(w,m)<ev(t[v],m);
		if(M)swap(t[v],w);
		if(r-l>1)L!=M?add_line(w,2*v,l,m):add_line(w,2*v+1,m,r);
	}
	ll get(int x,int v=1,int l=0,int r=0){
		if(!r)r=n;
		int m=(l+r)/2;
		ll y=ev(t[v],x);
		return r-l==1?y:min(y,x<m?get(x,2*v,l,m):get(x,2*v+1,m,r));
	}
};
