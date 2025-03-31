const int MOD=1e9+7;
struct M{
    ll val=0;
    M(ll x){val=(x%MOD+MOD)%MOD;}
    M()=default;
    template<class T>M operator+(T bt){M b(bt);M r(val);r.val+=b.val;if(r.val>=MOD)r.val-=MOD;return r;}
    template<class T>M operator-(T bt){M b(bt);M r(val);r.val+=MOD-b.val;if(r.val>=MOD)r.val-=MOD;return r;}
    template<class T>M operator*(T bt){M b(bt);M r(val);r.val*=b.val;r.val%=MOD;return r;}
    template<class T>M&operator+=(T bt){M b(bt);*this=*this+b;return*this;}
    template<class T>M&operator-=(T bt){M b(bt);*this=*this-b;return*this;}
    template<class T>M&operator*=(T bt){M b(bt);*this=*this*b;return*this;}
    M pow(ll e){M r(1);M a(val);while(e){if(e%2)r=r*a;a=a*a;e/=2;}return r;}
    template<class T>M operator/(T bt){M b(bt);M r(val);r*=b.pow(MOD-2).val;return r;}
    template<class T>M&operator/=(T bt){M b(bt);*this=*this/b;return*this;}
};
ostream&operator<<(ostream&s,M m){s<<m.val;return s;}
istream&operator>>(istream&s,M&m){s>>m.val;return s;}
