struct FT {
	vector<ll>s;
	FT(int n):s(n){}
	void upd(int i,int x){
		for(;i<sz(s);i|=i+1)s[i]+=x;
	}
	ll qry(int i){
		ll r=0;
		for(;i>0;i&=i-1)r+=s[i-1];
		return r;
	}
};

struct FT2 {
	vector<vi>ys;vector<FT>ft;
	FT2(int h):ys(h){}
	void inform(int x,int y){
		for(;x<sz(ys);x|=x+1)ys[x].pb(y);
	}
	void init(){
		for(vi&v:ys)sort(all(v)),ft.pb(sz(v));
	}
	int ind(int x,int y){
		return(int)(lower_bound(all(ys[x]),y)-ys[x].begin()); 
  }
	void upd(int x,int y,int dif){
		for(;x<sz(ys);x|=x+1)
			ft[x].upd(ind(x,y),dif);
	}
	ll qry(int x,int y){
		ll r=0;
		for(;x;x&=x-1)
			r+=ft[x-1].qry(ind(x-1,y));
		return r;
	}
  ll qry(int x1,int y1,int x2,int y2){
    return qry(x2,y2)-qry(x2,y1)-qry(x1,y2)+qry(x1,y1);
  }
};

