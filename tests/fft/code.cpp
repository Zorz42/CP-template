// cses: apples and bananas

// HEAD

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
