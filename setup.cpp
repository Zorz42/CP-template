/*
~/.vimrc

set number
set relativenumber
syntax enable
set autoindent
set tw=2
set tabstop=2
set shiftwidth=2
set expandtab
filetype plugin indent on
set wrap

Makefile

CXX = g++
CXXFLAGS = -std=c++20 -O2 -Wall

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

void solve(){
}

int main(){
	cin.tie(0);cout.tie(0);ios::sync_with_stdio(false);
	int t=1;cin>>t;
	while(t--)solve();
	return 0;
}
