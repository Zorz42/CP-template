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
#define sz(x) ((int)(x).size())
#define f1 first
#define f2 second
#define pb push_back
#define vc vector
typedef vc<int> vi;
typedef vc<ll> vl;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

#ifdef LOC
template<class A,class B>auto&operator<<(ostream&o,pair<A,B>p){return o<<"("<<p.f1<<", "<<p.f2<<")";}
template<class T>auto&operator<<(ostream&o,const vc<T>&v){o<<"{";for(int i=0;auto&x:v)o<<(i++?", ":"")<<x;return o<<"}";}
#define debug(x) cerr<<"[" #x "]: "<<x<<"\n";
#else
#define debug(x)
#endif

void solve(){
}

int main(){
	cin.tie(0);cout.tie(0);ios::sync_with_stdio(false);
	solve();return 0;
}
