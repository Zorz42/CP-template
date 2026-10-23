// gauss(a,p): a has n rows of m coefficients followed by the right side, all in [0,p) for prime p
// returns any solution of the system modulo p (free variables are 0), or empty vector if there is none
ll mpow(ll b,ll e,ll p){
	ll r=1;
	for(;e;e/=2,b=b*b%p)if(e&1)r=r*b%p;
	return r;
}

vl gauss(vc<vl>a,ll p){
	int n=sz(a),m=sz(a[0])-1,r=0;
	vi where(m,-1);
	for(int c=0;c<m&&r<n;c++){
		int s=r;
		while(s<n&&!a[s][c])s++;
		if(s==n)continue;
		swap(a[s],a[r]);
		ll inv=mpow(a[r][c],p-2,p);
		for(ll&v:a[r])v=v*inv%p;
		rep(i,n)if(i!=r&&a[i][c]){
			ll f=a[i][c];
			fwd(j,c,m+1)a[i][j]=(a[i][j]+(p-f)*a[r][j])%p;
		}
		where[c]=r++;
	}
	fwd(i,r,n)if(a[i][m])return{};
	vl x(m);
	rep(c,m)if(where[c]>=0)x[c]=a[where[c]][m];
	return x;
}
