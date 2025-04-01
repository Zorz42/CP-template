#define MINVPRECOMP 10000000
typedef long long ll;

const int MOD=1e9+7;
struct M{
    ll val=0;
		static ll inv[MINVPRECOMP+1];
		static ll calc_inv(ll i){ if(i<=MINVPRECOMP) return inv[i]; return (MOD-MOD/i)*calc_inv(MOD%i)%MOD; }
		static void precomp(){ inv[1]=1; for(ll i=2;i<=MINVPRECOMP;++i){ inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD; if(inv[i]<0) inv[i]+=MOD; } }
    M(ll x){val=(x%MOD+MOD)%MOD;}
    M()=default;
    template<class T>M operator+(T bt){M b(bt);M r(val);r.val+=b.val;if(r.val>=MOD)r.val-=MOD;return r;}
    template<class T>M operator-(T bt){M b(bt);M r(val);r.val+=MOD-b.val;if(r.val>=MOD)r.val-=MOD;return r;}
    template<class T>M operator*(T bt){M b(bt);M r(val);r.val*=b.val;r.val%=MOD;return r;}
    template<class T>M&operator+=(T bt){M b(bt);*this=*this+b;return*this;}
    template<class T>M&operator-=(T bt){M b(bt);*this=*this-b;return*this;}
    template<class T>M&operator*=(T bt){M b(bt);*this=*this*b;return*this;}
    M pow(ll e){M r(1);M a(val);while(e){if(e%2)r=r*a;a=a*a;e/=2;}return r;}

    template<class T>M operator/(T bt){ M b(bt); return M(val*M::calc_inv(b.val)); }
    template<class T>M&operator/=(T bt){M b(bt);*this*=M::calc_inv(b.val);return*this;}
};
ostream&operator<<(ostream&s,M m){s<<m.val;return s;}
istream&operator>>(istream&s,M&m){s>>m.val;return s;}

//	Add `M::precomp();` to start of main
