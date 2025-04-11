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

// ALGO

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
