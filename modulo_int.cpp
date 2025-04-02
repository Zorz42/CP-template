const int MOD=1e9+7,PC=1e7;
ll M_inv[PC+1];
struct M{
	ll val=0;
	static void precomp(){M_inv[1]=1;for(ll i=2;i<=PC;++i){
		M_inv[i]=(MOD-MOD/i)*M_inv[MOD%i]%MOD;if(M_inv[i]<0)M_inv[i]+=MOD;}}
	static ll calc_inv(ll i){if(i<=PC)return M_inv[i];
		return(MOD-MOD/i)*calc_inv(MOD%i)%MOD;}
	M(ll x){val=(x%MOD+MOD)%MOD;}
	M()=default;
	template<class T>bool operator==(T b){return val==M(b).val;}
	template<class T>bool operator!=(T b){return val!=M(b).val;}
	template<class T>M operator+(T bt){M b(bt);M r(val);r.val+=b.val;if(r.val>=MOD)
		r.val-=MOD;return r;}
	template<class T>M operator-(T bt){M b(bt);M r(val);r.val+=MOD-b.val;if(r.val>=MOD)
		r.val-=MOD;return r;}
	template<class T>M operator*(T bt){M b(bt);M r(val);r.val*=b.val;r.val%=MOD;return r;}
	template<class T>M&operator+=(T bt){M b(bt);*this=*this+b;return*this;}
	template<class T>M&operator-=(T bt){M b(bt);*this=*this-b;return*this;}
	template<class T>M&operator*=(T bt){M b(bt);*this=*this*b;return*this;}
	M pow(ll e){M r(1);M a(val);while(e){if(e%2)r=r*a;a=a*a;e/=2;}return r;}
	template<class T>M operator/(T bt){ M b(bt); return M(val*calc_inv(b.val)); }
	template<class T>M&operator/=(T bt){M b(bt);*this*=calc_inv(b.val);return*this;}
};
namespace std{template<>struct hash<M>{
	inline size_t operator()(const M&x)const{return x.val;}
};}
template<class T>bool operator<(T at,T bt){M b(bt);M a(at);return a.val<b.val;}
ostream&operator<<(ostream&s,M m){s<<m.val;return s;}
istream&operator>>(istream&s,M&m){s>>m.val;return s;}
