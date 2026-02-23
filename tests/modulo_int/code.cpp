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

// ALGO

bool test1(){
    // test constructor, == and !=
    ll a=rand();
    return M(a)==a&&!(M(a)!=a);
}

bool test2(){
    // test !=
    M a=rand()%20;
    M b=rand()%20;
    return(a==b)+(a!=b)==1;
}

bool test3(){
    // test +, -, *
    ll a=rand()%MOD;
    ll b=rand()%MOD;
    return M(a)+M(b)==(a+b)%MOD&&M(a)-M(b)==(a+MOD-b)%MOD&&M(a)*M(b)==(a*b)%MOD;
}

bool test4(){
    // test +, -, * with negative
    ll a=rand()%MOD;
    ll b=rand()%MOD;
    return M(a-MOD)+M(b-MOD)==(a+b)%MOD&&M(a-MOD)-M(b-MOD)==(a+MOD-b)%MOD&&M(a-MOD)*M(b-MOD)==a*b%MOD;
}

bool test5(){
    // test +=, -=, *=
    ll a=rand()%MOD;
    ll b=rand()%MOD;
    M ma1=a;
    ma1+=b;
    M ma2=a;
    ma2-=b;
    M ma3=a;
    ma3*=b;
    return ma1==(a+b)%MOD&&ma2==(a-b+MOD)%MOD&&ma3==a*b%MOD;
}

bool test6(){
    // test powers
    int p=rand()%100;
    M b=rand()%MOD;
    M a=1;
    for(int i=0;i<p;i++)
        a*=b;
    return b.pow(p)==a;
}

bool test7(){
    // test if various things compile
    set<M>a1;
    a1.insert(0);
    a1.erase(0);
    map<M,M>a2;
    unordered_map<M,M>a3;
    // not done yet
    /*1+M(1);
    1-M(1);
    1*M(1);
    1/M(1);*/
    return true;
}

bool test8(){
    // test inverses
    M a=rand()%MOD;
    return M(1)/a==a.pow(MOD-2);
}

void solve(){
    int a;
    cin>>a;
    for(int i=0;i<1000;i++){
        bool res=false;
        if(a==1)res=test1();
        if(a==2)res=test2();
        if(a==3)res=test3();
        if(a==4)res=test4();
        if(a==5)res=test5();
        if(a==6)res=test6();
        if(a==7)res=test7();
        if(a==8)res=test8();
        if(!res){
            cout<<"ERR\n";
            return;
        }
    }
    cout<<"OK\n";
}

int main(){
    M::precomp();
    ios::sync_with_stdio(false);cout.tie(0);cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solve();
    return 0;
}

/*

 */
