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

typedef pair<ll,ll>line;

struct LCT{
    int n;
    vector<line>lines;

    LCT(int n):n(n){
        lines=vector<line>(4*n,{0,1e18});
    }

    ll ev(line a,int x){
        return a.first*x+a.second;
    }

    void add_line(line nw,int v,int l,int r){
        int m=(l+r)/2;
        bool lef=ev(nw,l)<ev(lines[v],l);
        bool mid=ev(nw,m)<ev(lines[v],m);
        if(mid)
            swap(lines[v],nw);
        if(r-l==1)
            return;
        else if(lef!=mid)
            add_line(nw,2*v,l,m);
        else
            add_line(nw,2*v+1,m,r);
    }

    void add_line(line nw){
        add_line(nw,1,0,n);
    }

    ll get(int x,int v,int l,int r){
        int m=(l+r)/2;
        if(r-l==1)
            return ev(lines[v],x);
        else if(x<m)
            return min(ev(lines[v],x),get(x,2*v,l,m));
        else
            return min(ev(lines[v],x),get(x,2*v+1,m,r));
    }

    ll get(int x){
        return get(x,1,0,n);
    }
};

void solve(){
    int n,x;
    cin>>n>>x;
    vector<int>s(n),f(n);
    for(int&i:s)
        cin>>i;
    for(int&i:f)
        cin>>i;

    LCT tree(1e6);

    vector<ll>dp(n);
    for(int i=n-2;i>=0;i--){
        tree.add_line({s[i+1],dp[i+1]});
        dp[i]=tree.get(f[i]);
    }
    ll res=1e18;
    for(int i=0;i<n;i++)
        res=min(res,dp[i]+1LL*s[i]*x);
    cout<<res<<"\n";
}

int main(){
    ios::sync_with_stdio(false);cout.tie(0);cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solve();
    return 0;
}

/*

 */
