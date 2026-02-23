
const int HMOD=1e9+7;
const int HX=31;

class FastString{
    string str;
    vector<ll>hashes;
    vector<ll>pows;
    int len;
public:
    FastString(string str):str(str){
        len=(int)str.size();
        hashes.resize(len+1);
        pows.resize(len+1);
        pows[0]=1;
        for(int i=1;i<=len;i++)
            pows[i]=(pows[i-1]*HX)%HMOD;
        
        hashes[0]=0;
        for(int i=1;i<=len;i++)
            hashes[i]=(hashes[i-1]+pows[i-1]*(str[i-1]-'a'+1))%HMOD;
    }
    
    ll get(int l,int r){
        ll hsh=hashes[r]+HMOD-hashes[l];
        hsh%=HMOD;
        hsh*=pows[len-l];
        hsh%=HMOD;
        return hsh;
    }
};
