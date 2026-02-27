// cses: forest queries II

// HEAD

// ALGO


int mat[1000][1000];
void solve(){
  int n,q;
  cin>>n>>q;
  FT2 tree(1000);
  vector<pii>trees;
  rep(y,n){
    string s;
    cin>>s;
    rep(x,n){
      if(s[x]=='*'){
        trees.pb({x,y});
        tree.inform(x,y);
      }
    }
  }
  vector<vi>qrs;
  rep(i,q){
    int t,x1,y1;
    cin>>t>>y1>>x1;
    x1--;y1--;
    if(t==1){
      qrs.pb({t,x1,y1});
      tree.inform(x1,y1);
    }else{
      int x2,y2;
      cin>>y2>>x2;
      qrs.pb({t,x1,y1,x2,y2});
    }
  }
  tree.init();
  for(auto[x,y]:trees){
    tree.upd(x,y,1);
    mat[x][y]=1;
  }
  for(auto v:qrs){
    if(v[0]==1){
      int x=v[1],y=v[2];
      if(mat[x][y]){
        tree.upd(x,y,-1);
      }else{
        tree.upd(x,y,1);
      }
      mat[x][y]^=1;
    }else{
      int x1=v[1],y1=v[2],x2=v[3],y2=v[4];
      cout<<tree.qry(x1,y1,x2,y2)<<"\n";
    }
  }
}

int main(){
    ios::sync_with_stdio(false);cout.tie(0);cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solve();
    return 0;
}
