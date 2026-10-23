// HEAD

// ALGO

mt19937_64 rng(42);

bool check(ll a,ll b){
    ll x,y;
    ll g=gcd(a,b,x,y);
    if(g!=std::gcd(a,b))return false;
    if((__int128)a*x+(__int128)b*y!=g)return false;
    return g==0||(abs(x)<=max(b/g,1LL)&&abs(y)<=max(a/g,1LL));
}

bool test1(){
    return check(rng()%1000,rng()%1000);
}

bool test2(){
    return check(rng()%(ll)1e18,rng()%(ll)1e18);
}

bool test3(){
    ll a=rng()%(ll)1e9,b=rng()%(ll)1e9,k=rng()%(ll)1e9;
    return check(a*k,b*k)&&check(a,0)&&check(0,a)&&check(a,a);
}

bool test4(){
    ll a=1,b=1;
    while(b<(ll)4e17){
        if(!check(a,b)||!check(b,a))return false;
        ll c=a+b;a=b;b=c;
    }
    return true;
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
        if(!res){
            cout<<"ERR\n";
            return;
        }
    }
    cout<<"OK\n";
}

int main(){
    ios::sync_with_stdio(false);cout.tie(0);cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solve();
    return 0;
}
