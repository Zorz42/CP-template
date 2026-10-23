vi suffix_array(string s){
	s.pb(0);
	int n=sz(s);
	vi p(n),c(all(s)),t(n),cnt(max(256,n));
	iota(all(p),0);
	sort(all(p),[&](int a,int b){return c[a]<c[b];});
	for(int k=1;;k*=2){
		rep(i,n)t[i]=(p[i]-k+n)%n;
		fill(all(cnt),0);
		for(int x:c)cnt[x]++;
		partial_sum(all(cnt),cnt.begin());
		for(int i=n;i--;)p[--cnt[c[t[i]]]]=t[i];
		t[p[0]]=0;
		fwd(i,1,n)t[p[i]]=t[p[i-1]]+(pii(c[p[i]],c[(p[i]+k)%n])!=pii(c[p[i-1]],c[(p[i-1]+k)%n]));
		c.swap(t);
		if(c[p[n-1]]==n-1)break;
	}
	p.erase(p.begin());
	return p;
}

// p is suffix array (which is needed)
vi lcp(const string&s,const vi&p){
	int n=sz(s),k=0;
	vi r(n),l(n-1);
	rep(i,n)r[p[i]]=i;
	rep(i,n)if(r[i]<n-1){
		int j=p[r[i]+1];
		while(max(i,j)+k<n&&s[i+k]==s[j+k])k++;
		l[r[i]]=k;
		k-=!!k;
	}else k=0;
	return l;
}
