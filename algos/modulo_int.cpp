// M: integer modulo MOD (MOD must be prime for division)
// supports + - * / and assignment versions, pow, == != <, cin, cout and use as key in set, map and unordered_map
const ll MOD=1e9+7;
struct M{
	ll val;
	M(ll x=0):val((x%MOD+MOD)%MOD){}
	M&operator+=(M b){if((val+=b.val)>=MOD)val-=MOD;return*this;}
	M&operator-=(M b){if((val-=b.val)<0)val+=MOD;return*this;}
	M&operator*=(M b){val=val*b.val%MOD;return*this;}
	M&operator/=(M b){return*this*=b.pow(MOD-2);}
	friend M operator+(M a,M b){return a+=b;}
	friend M operator-(M a,M b){return a-=b;}
	friend M operator*(M a,M b){return a*=b;}
	friend M operator/(M a,M b){return a/=b;}
	friend bool operator==(M a,M b){return a.val==b.val;}
	friend bool operator!=(M a,M b){return a.val!=b.val;}
	bool operator<(M b)const{return val<b.val;}
	M pow(ll e)const{M r=1,a=*this;for(;e;e/=2,a*=a)if(e&1)r*=a;return r;}
	friend ostream&operator<<(ostream&s,M m){return s<<m.val;}
	friend istream&operator>>(istream&s,M&m){ll x;s>>x;m=x;return s;}
};
template<>struct std::hash<M>{size_t operator()(M x)const{return x.val;}};
