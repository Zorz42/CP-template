using cd=complex<double>;
const double PI=acos(-1);

void fft(vector<cd>&a,bool invert){
    int n=(int)a.size();
    if(n==1)
        return;
    vector<cd>a0(n/2),a1(n/2);
    for(int i=0;2*i<n;i++){
        a0[i]=a[2*i];
        a1[i]=a[2*i+1];
    }
    fft(a0,invert);
    fft(a1,invert);
    double ang=2*PI/n*(invert?-1:1);
    cd w(1),wn(cos(ang),sin(ang));
    for(int i=0;2*i<n;i++){
        a[i]=a0[i]+w*a1[i];
        a[i+n/2]=a0[i]-w*a1[i];
        if(invert){
            a[i]/=2;
            a[i+n/2]/=2;
        }
        w*=wn;
    }
}

// polynomial multiplication
vector<ll>multiply(vector<int>&a,vector<int>&b){
    vector<cd>fa(a.begin(),a.end()),fb(b.begin(),b.end());
    int n=1;
    while(n<int(a.size()+b.size()))
        n<<=1;
    fa.resize(n);
    fb.resize(n);
    fft(fa,0);
    fft(fb,0);
    for (int i=0;i<n;i++)
        fa[i]*=fb[i];
    fft(fa,1);
    vector<ll>result(n);
    for(int i=0;i<n;i++)
        result[i]=round(fa[i].real());
    return result;
}
