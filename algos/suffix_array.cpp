vi suffix_array(string s){
	s.pb('$');
	int n=sz(s);
	const int A=256;
	vi p(n),c(n),cnt(max(A,n),0);
	rep(i,n)
		cnt[s[i]]++;
	fwd(i,1,A)
		cnt[i]+=cnt[i-1];
	rep(i,n)
		p[--cnt[s[i]]]=i;
	c[p[0]]=0;
	int cl=1;
	fwd(i,1,n){
		if(s[p[i]]!=s[p[i-1]])
			cl++;
		c[p[i]]=cl-1;
	}
	vi pn(n),cn(n);
	for(int h=0;(1<<h)<n;h++){
		rep(i,n){
			pn[i]=p[i]-(1<<h);
			if(pn[i]<0)
				pn[i]+=n;
		}
		fill(cnt.begin(),cnt.begin()+cl,0);
		rep(i,n)
			cnt[c[pn[i]]]++;
		fwd(i,1,cl)
			cnt[i]+=cnt[i-1];
		for(int i=n-1;i>=0;i--)
			p[--cnt[c[pn[i]]]]=pn[i];
		cn[p[0]]=0;
		cl=1;
		fwd(i,1,n){
			pii cur={c[p[i]],c[(p[i]+(1<<h))%n]};
			pii prev={c[p[i-1]],c[(p[i-1]+(1<<h))%n]};
			if(cur!=prev)
				cl++;
			cn[p[i]]=cl-1;
		}
		c.swap(cn);
	}
	p.erase(p.begin());
	return p;
}
 
// p is suffix array (which is needed)
vi lcp(string s,vi p) {
	int n=sz(s);
	vi r(n,0);
	rep(i,n)
		r[p[i]]=i;
	int k=0;
	vi l(n-1,0);
	rep(i,n){
		if(r[i]==n-1){
			k=0;
			continue;
		}
		int j=p[r[i]+1];
		while(i+k<n&&j+k<n&&s[i+k]==s[j+k])
			k++;
		l[r[i]]=k;
		if(k)
			k--;
	}
	return l;
}
