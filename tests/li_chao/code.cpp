// cses: monster game II

// HEAD

// ALGO

void solve(){
    int n,x;
    cin>>n>>x;
    vector<int>s(n),f(n);
    for(int&i:s)
        cin>>i;
    for(int&i:f)
        cin>>i;

    LCT tree(1e6);

    vector<ll>dp(n);
    for(int i=n-2;i>=0;i--){
        tree.add_line({s[i+1],dp[i+1]});
        dp[i]=tree.get(f[i]);
    }
    ll res=1e18;
    for(int i=0;i<n;i++)
        res=min(res,dp[i]+1LL*s[i]*x);
    cout<<res<<"\n";
}

int main(){
    ios::sync_with_stdio(false);cout.tie(0);cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solve();
    return 0;
}

/*

 */
