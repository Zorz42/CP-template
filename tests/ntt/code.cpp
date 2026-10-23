// HEAD

// ALGO

mt19937 rng(42);

vl rand_poly(int n){
    vl a(n);
    for(ll&x:a)
        x=rng()%NM;
    return a;
}

vl naive(const vl&a,const vl&b){
    if(a.empty()||b.empty())return{};
    vl c(sz(a)+sz(b)-1);
    rep(i,sz(a))
        rep(j,sz(b))
            c[i+j]=(c[i+j]+a[i]*b[j])%NM;
    return c;
}

ll eval(const vl&a,ll x){
    ll r=0;
    for(int i=sz(a)-1;i>=0;i--)
        r=(r*x+a[i])%NM;
    return r;
}

bool test1(){
    vl a=rand_poly(rng()%4),b=rand_poly(rng()%4);
    return ntt_multiply(a,b)==naive(a,b);
}

bool test2(){
    vl a=rand_poly(rng()%100),b=rand_poly(rng()%100);
    return ntt_multiply(a,b)==naive(a,b);
}

bool test3(){
    vl a=rand_poly(rng()%2000+1),b=rand_poly(rng()%2000+1);
    return ntt_multiply(a,b)==naive(a,b);
}

bool test4(){
    vl a(rng()%50+1,NM-1),b(rng()%50+1,NM-1);
    return ntt_multiply(a,b)==naive(a,b);
}

bool test5(){
    vl a=rand_poly(500000),b=rand_poly(500000),c=ntt_multiply(a,b);
    ll x=rng()%NM;
    return sz(c)==999999&&eval(c,x)==eval(a,x)*eval(b,x)%NM;
}

void solve(){
    int a;
    cin>>a;
    int its=a==5?3:a==3?20:1000;
    for(int i=0;i<its;i++){
        bool res=false;
        if(a==1)res=test1();
        if(a==2)res=test2();
        if(a==3)res=test3();
        if(a==4)res=test4();
        if(a==5)res=test5();
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
