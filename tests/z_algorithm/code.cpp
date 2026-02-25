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

// cses: string matching

// ALGO

void solve(){
	string a,b;
	cin>>b>>a;
	vector<int>res=z_function(a+b);
	int r=0;
	int n=(int)a.size(),m=(int)b.size();
	for(int i=n;i<n+m;i++)
		r+=res[i]>=n;
	cout<<r<<"\n";
}

int main(){
    ios::sync_with_stdio(false);cout.tie(0);cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solve();
    return 0;
}

/*

 */
