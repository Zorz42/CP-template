// FT(n): n zeros, upd(i,x): a[i]+=x, qry(i): a[0]+...+a[i-1]
struct FT{
	vl s;
	FT(int n):s(n){}
	void upd(int i,ll x){
		for(;i<sz(s);i|=i+1)s[i]+=x;
	}
	ll qry(int i){
		ll r=0;
		for(;i>0;i&=i-1)r+=s[i-1];
		return r;
	}
};

// FT2(h): 2D sums over points with 0<=x<h, all points that will be updated must be known in advance
// inform(x,y) for every such point, then init(), then use upd and qry
// upd(x,y,d): value at (x,y)+=d
// qry(x,y): sum over x'<x,y'<y, qry(x1,y1,x2,y2): sum over x1<=x'<x2,y1<=y'<y2
struct FT2{
	vc<vi>ys;vc<FT>ft;
	FT2(int h):ys(h){}
	void inform(int x,int y){
		for(;x<sz(ys);x|=x+1)ys[x].pb(y);
	}
	void init(){
		for(vi&v:ys)sort(all(v)),v.erase(unique(all(v)),v.end()),ft.pb(sz(v));
	}
	int ind(int x,int y){
		return lower_bound(all(ys[x]),y)-ys[x].begin();
	}
	void upd(int x,int y,ll dif){
		for(;x<sz(ys);x|=x+1)ft[x].upd(ind(x,y),dif);
	}
	ll qry(int x,int y){
		ll r=0;
		for(;x;x&=x-1)r+=ft[x-1].qry(ind(x-1,y));
		return r;
	}
	ll qry(int x1,int y1,int x2,int y2){
		return qry(x2,y2)-qry(x2,y1)-qry(x1,y2)+qry(x1,y1);
	}
};
