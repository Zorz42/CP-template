template<typename T>
struct SegTree{
    int n;
    vector<T>t;
    T (*m)(T,T);
    
    // n = size, d = default value, m = merge function
    SegTree(int n,T d,T(*m)(T,T)):n(n),m(m){
        t=vector<T>(2*n,d);
        for(int i=n-1;i>0;i--)
            t[i]=m(t[2 * i],t[2 * i + 1]);
    }
    
    void upd(int i,T x){
        i+=n;
        t[i]=x;
        while(i>1){
            i/=2;
            t[i]=m(t[2*i],t[2*i+1]);
        }
    }
    
    T get(int l,int r){
        l+=n;
        r+=n;
        T rs=t[l];
        l++;
        while(l<r){
            if(l%2){
                rs=m(rs,t[l]);
                l++;
            }
            if(r%2){
                r--;
                rs=m(rs,t[r]);
            }
            l/=2;
            r/=2;
        }
        return rs;
    }
};
