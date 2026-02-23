const ll MOD=100000004987;
 
ll primes[]={
    1000000007,
    1000000207,
    1000000409,
    1000000531,
    1000000829,
    1000001021,
    1000001269,
    1000001447,
};
 
int n;
vector<int>nodes[100000];
int sub_size[100000];
 
void init_tree(int node,int par){
    sub_size[node]=1;
    for(int ne:nodes[node]){
        if(ne!=par){
            init_tree(ne,node);
            sub_size[node]+=sub_size[ne];
        }
    }
}
 
ll hash_tree(int node,int par,int depth){
    ll prime=primes[(depth+sub_size[node])%8];
    
    if(nodes[node].size()==1&&node!=par){
        return prime;
    }
    
    vector<ll>hashes;
    for(int ne:nodes[node]){
        if(ne==par)
            continue;
        hashes.push_back(hash_tree(ne,node,depth+1));
    }
    sort(hashes.begin(),hashes.end());
    ll res=0;
    ll cp=prime;
    for(ll i:hashes){
        res+=cp*i;
        res%=MOD;
        cp*=prime;
        cp%=MOD;
    }
    
    /*if(par==0||node==0)
        cout<<res<<"\n";*/
    
    return res;
}
 
pair<int,int> get_centroid(int node,int par){
    int biggest=-1;
    for(int ne:nodes[node]){
        if(ne==par)
            continue;
        if(biggest==-1||sub_size[ne]>sub_size[biggest])
            biggest=ne;
    }
    
    if(sub_size[biggest]<=sub_size[0]/2)
        return {node,biggest};
    return get_centroid(biggest,node);
}

// USAGE
cin>>n;
for(int i=0;i<n;i++)
	nodes[i].clear();
for(int i=0;i<n-1;i++){
	int a,b;
	cin>>a>>b;
	a--;b--;
	nodes[a].push_back(b);
	nodes[b].push_back(a);
}
init_tree(0,0);
pair<int,int> root=get_centroid(0,0);
init_tree(root.first,root.first);
ll hash11=hash_tree(root.first,root.first,0);
init_tree(root.second,root.second);
ll hash12=hash_tree(root.second,root.second,0);

for(int i=0;i<n;i++)
	nodes[i].clear();
for(int i=0;i<n-1;i++){
	int a,b;
	cin>>a>>b;
	a--;b--;
	nodes[a].push_back(b);
	nodes[b].push_back(a);
}
init_tree(0,0);
root=get_centroid(0,0);
init_tree(root.first,root.first);
ll hash21=hash_tree(root.first,root.first,0);
init_tree(root.second,root.second);
ll hash22=hash_tree(root.second,root.second,0);

cout<<((hash11==hash21||hash12==hash22||hash11==hash22||hash12==hash21)?"YES\n":"NO\n");
