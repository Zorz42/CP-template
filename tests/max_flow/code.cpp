// cses: download speed

// HEAD

// ALGO

void solve(){
    int n,m;
    cin>>n>>m;
    MaxFlow g(n);
    for(int i=0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        g.add(a-1,b-1,c);
    }
    cout<<g.maxflow(0,n-1)<<"\n";
}

int main(){
    ios::sync_with_stdio(false);cout.tie(0);cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solve();
    return 0;
}

/*

 */
