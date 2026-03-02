struct LCT{
	int n;
	vc<pll>lines;

	LCT(int n):n(n){
		lines=vc<pll>(4*n,{0,1e18});
	}

	ll ev(pll a,int x){
		return a.f1*x+a.f2;
	}

	void add_line(pll nw,int v,int l,int r){
		int m=(l+r)/2;
		bool lef=ev(nw,l)<ev(lines[v],l);
		bool mid=ev(nw,m)<ev(lines[v],m);
		if(mid)
			swap(lines[v],nw);
		if(r-l==1)
			return;
		else if(lef!=mid)
			add_line(nw,2*v,l,m);
		else
			add_line(nw,2*v+1,m,r);
	}

	void add_line(pll nw){
		add_line(nw,1,0,n);
	}

	ll get(int x,int v,int l,int r){
		int m=(l+r)/2;
		if(r-l==1)
			return ev(lines[v],x);
		else if(x<m)
			return min(ev(lines[v],x),get(x,2*v,l,m));
		else
			return min(ev(lines[v],x),get(x,2*v+1,m,r));
	}

	ll get(int x){
		return get(x,1,0,n);
	}
};
