using cd=complex<double>;
const double PI=acos(-1);

void fft(vc<cd>&a,bool inv){
	int n=(int)a.size();
	if(n==1)
		return;
	vc<cd>a0(n/2),a1(n/2);
	rep(i,(n+1)/2){
		a0[i]=a[2*i];
		a1[i]=a[2*i+1];
	}
	fft(a0,inv);
	fft(a1,inv);
	double ang=2*PI/n*(inv?-1:1);
	cd w(1),wn(cos(ang),sin(ang));
	rep(i,(n+1)/2){
		a[i]=a0[i]+w*a1[i];
		a[i+n/2]=a0[i]-w*a1[i];
		if(inv){
			a[i]/=2;
			a[i+n/2]/=2;
		}
		w*=wn;
	}
}

// polynomial multiplication
vl multiply(vi&a,vi&b){
	vc<cd>fa(all(a)),fb(all(b));
	int n=1;
	while(n<sz(a)+sz(b))
		n<<=1;
	fa.resize(n);
	fb.resize(n);
	fft(fa,0);
	fft(fb,0);
	rep(i,n)
		fa[i]*=fb[i];
	fft(fa,1);
	vc<ll>res(n);
	rep(i,n)
		res[i]=round(fa[i].real());
	return res;
}
