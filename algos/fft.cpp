// multiply(a,b): coefficients of the product of polynomials a and b
// exact while (sum of a[i]^2 + sum of b[i]^2)*log2(n) < 9e14
typedef complex<double> C;
void fft(vc<C>&a){
	int n=sz(a),L=__builtin_ctz(n);
	static vc<complex<long double>>R(2,1);
	static vc<C>rt(2,1);
	for(static int k=2;k<n;k*=2){
		R.resize(n);rt.resize(n);
		auto x=polar(1.0L,acosl(-1)/k);
		fwd(i,k,2*k)rt[i]=R[i]=i&1?R[i/2]*x:R[i/2];
	}
	vi rev(n);
	rep(i,n)rev[i]=(rev[i/2]|(i&1)<<L)/2;
	rep(i,n)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int k=1;k<n;k*=2)for(int i=0;i<n;i+=2*k)rep(j,k){
		C z=rt[j+k]*a[i+j+k];
		a[i+j+k]=a[i+j]-z;
		a[i+j]+=z;
	}
}

vl multiply(const vi&a,const vi&b){
	if(a.empty()||b.empty())return{};
	vl res(sz(a)+sz(b)-1);
	int n=1;
	while(n<sz(res))n*=2;
	vc<C>in(n),out(n);
	rep(i,sz(a))in[i].real(a[i]);
	rep(i,sz(b))in[i].imag(b[i]);
	fft(in);
	for(C&x:in)x*=x;
	rep(i,n)out[i]=in[-i&(n-1)]-conj(in[i]);
	fft(out);
	rep(i,sz(res))res[i]=llround(imag(out[i])/(4*n));
	return res;
}
