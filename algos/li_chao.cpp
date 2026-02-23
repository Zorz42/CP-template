typedef pair<ll,ll>line;

struct LCT{
    int n;
    vector<line>lines;

    LCT(int n):n(n){
        lines=vector<line>(4*n,{0,1e18});
    }

    ll ev(line a,int x){
        return a.first*x+a.second;
    }

    void add_line(line nw,int v,int l,int r){
        int m=(l+r)/2;
        bool lef=ev(nw,l)<ev(lines[v],l);
        bool mid=ev(nw,m)<ev(lines[v],m);
        if(mid)
            swap(lines[v],nw);
        if(r-l==1)
            return;
        else if(lef!=mid)
            add_line(nw,2*v,l,m);
        else
            add_line(nw,2*v+1,m,r);
    }

    void add_line(line nw){
        add_line(nw,1,0,n);
    }

    ll get(int x,int v,int l,int r){
        int m=(l+r)/2;
        if(r-l==1)
            return ev(lines[v],x);
        else if(x<m)
            return min(ev(lines[v],x),get(x,2*v,l,m));
        else
            return min(ev(lines[v],x),get(x,2*v+1,m,r));
    }

    ll get(int x){
        return get(x,1,0,n);
    }
};