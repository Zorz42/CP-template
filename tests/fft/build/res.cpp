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
#include<complex>
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
using namespace std;

using cd=complex<double>;
const double PI=acos(-1);

void fft(vector<cd>&a,bool invert){
    int n=(int)a.size();
    if(n==1)
        return;
    vector<cd>a0(n/2),a1(n/2);
    for(int i=0;2*i<n;i++){
        a0[i]=a[2*i];
        a1[i]=a[2*i+1];
    }
    fft(a0,invert);
    fft(a1,invert);
    double ang=2*PI/n*(invert?-1:1);
    cd w(1),wn(cos(ang),sin(ang));
    for(int i=0;2*i<n;i++){
        a[i]=a0[i]+w*a1[i];
        a[i+n/2]=a0[i]-w*a1[i];
        if(invert){
            a[i]/=2;
            a[i+n/2]/=2;
        }
        w*=wn;
    }
}

// polynomial multiplication
vector<ll>multiply(vector<int>&a,vector<int>&b){
    vector<cd>fa(a.begin(),a.end()),fb(b.begin(),b.end());
    int n=1;
    while(n<int(a.size()+b.size()))
        n<<=1;
    fa.resize(n);
    fb.resize(n);
    fft(fa,0);
    fft(fb,0);
    for (int i=0;i<n;i++)
        fa[i]*=fb[i];
    fft(fa,1);
    vector<ll>result(n);
    for(int i=0;i<n;i++)
        result[i]=round(fa[i].real());
    return result;
}


void solve(){
    int k,n,m;
    cin>>k>>n>>m;
    vector<int>a(k+1),b(k+1);
    for(int i=0;i<n;i++){
        int c;
        cin>>c;
        a[c]++;
    }
    for(int i=0;i<m;i++){
        int c;
        cin>>c;
        b[c]++;
    }
    vector<ll>res=multiply(a,b);
    for(int i=2;i<=2*k;i++)
        cout<<res[i]<<" ";
    cout<<"\n";
}

int main(){
    ios::sync_with_stdio(false);cout.tie(0);cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solve();
    return 0;
}

/*

 */
