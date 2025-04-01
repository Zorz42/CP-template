#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<limits.h>
#include<math.h>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<iomanip>
#include<cstring>
#include<random>
#include<cassert>
#include<sstream>
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
using namespace std;
//
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

// ALGO

void solve(){
    int n,m;
    cin>>n>>m;
    MaxFlow g(n);
    for(int i=0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        g.add(a-1,b-1,c);
    }
    cout<<g.maxflow(0,n-1)<<"\n";
}

int main(){
    ios::sync_with_stdio(false);cout.tie(0);cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solve();
    return 0;
}

/*

 */