// ntt_multiply(a,b): coefficients of the product of polynomials a and b modulo NM, coefficients must be in [0,NM)
// works for any prime NM=c*2^k+1 with primitive root NG while the result has at most 2^k coefficients
const ll NM=998244353,NG=3;
ll npow(ll b,ll e){
	ll r=1;
	for(;e;e/=2,b=b*b%NM)if(e&1)r=r*b%NM;
	return r;
}

void ntt(vl&a,bool inv){
	int n=sz(a);
	for(int i=1,j=0;i<n;i++){
		int bit=n>>1;
		for(;j&bit;bit>>=1)j^=bit;
		j^=bit;
		if(i<j)swap(a[i],a[j]);
	}
	for(int k=1;k<n;k*=2){
		ll w=npow(NG,(NM-1)/(2*k));
		if(inv)w=npow(w,NM-2);
		for(int i=0;i<n;i+=2*k){
			ll z=1;
			rep(j,k){
				ll u=a[i+j],v=a[i+j+k]*z%NM;
				a[i+j]=u+v<NM?u+v:u+v-NM;
				a[i+j+k]=u-v>=0?u-v:u-v+NM;
				z=z*w%NM;
			}
		}
	}
	if(inv){
		ll ni=npow(n,NM-2);
		for(ll&x:a)x=x*ni%NM;
	}
}

vl ntt_multiply(vl a,vl b){
	if(a.empty()||b.empty())return{};
	int s=sz(a)+sz(b)-1,n=1;
	while(n<s)n*=2;
	a.resize(n);b.resize(n);
	ntt(a,0);ntt(b,0);
	rep(i,n)a[i]=a[i]*b[i]%NM;
	ntt(a,1);
	a.resize(s);
	return a;
}
