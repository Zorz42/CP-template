/*

setxkbmap us -option caps:escape

~/.vimrc

set number relativenumber tabstop=2 shiftwidth=2 autoindent
syntax enable
filetype plugin indent on

Makefile:

%: %.cpp
	g++ -std=c++20 -O2 -Wall -DLOC $< -o $@

 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fwd(i,a,b) for(int i=(a); i<(b);i++)
#define rep(i,n) fwd(i,0,n)
#define all(x) (x).begin(), (x).end()
#define sz(x)((int)(x).size())
#define f1 first
#define f2 second
#define pb push_back
#define vc vector
typedef vc<int> vi;
typedef vc<ll> vl;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

#ifdef LOC
template<typename T1,typename T2>
auto& operator<<(ostream& out, pair<T1, T2> a) {return out<<"("<<a.st<<", "<<a.nd<<")";}
template<typename T>
auto& operator<<(ostream& out, vector<T>& a) {
	out<<"{";
	int cnt=0;
	for(auto b:a){
		cnt++;
		out<<b;
		if(cnt!=a.size())
			out<<", ";
	}
	return out<<"}";
}
 
#define debug(x) cerr<<"[" #x "]: "<<x<<"\n";
#else
#define debug(x) ;
#endif

void solve(){
}

int main(){
	cin.tie(0);cout.tie(0);ios::sync_with_stdio(false);
	int t=1;//cin>>t;
	while(t--)solve();
	return 0;
}
