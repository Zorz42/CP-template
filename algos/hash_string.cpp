// FastString(s): get(l,r) returns hash of s[l..r-1], equal substrings have equal hashes
typedef unsigned long long ull;
const ull HM=(1ull<<61)-1,HB=chrono::steady_clock::now().time_since_epoch().count()%HM;
ull hmul(ull a,ull b){
	__uint128_t c=(__uint128_t)a*b;
	ull r=(c&HM)+(c>>61);
	return r>=HM?r-HM:r;
}

struct FastString{
	vc<ull>h,p;
	FastString(const string&s):h(sz(s)+1),p(sz(s)+1,1){
		rep(i,sz(s))h[i+1]=(hmul(h[i],HB)+s[i])%HM,p[i+1]=hmul(p[i],HB);
	}
	ull get(int l,int r){
		return(h[r]+HM-hmul(h[l],p[r-l]))%HM;
	}
};
