const int HMOD1=1e9+7;
const int HMOD2=1e9+9;
const int HX1=31;
const int HX2=29;
 
struct FastString{
	string s;
	vc<ll>h1,h2,p1,p2;
	FastString(string s):s(s){
		p1={1};
		fwd(i,1,sz(s)+1)
			p1.pb((p1[i-1]*HX1)%HMOD1);
		p2={1};
		fwd(i,1,sz(s)+1)
			p2.pb((p2[i-1]*HX2)%HMOD2);
		h1={1};
		fwd(i,1,sz(s)+1)
			h1.pb((h1[i-1]+p1[i-1]*(s[i-1]-'a'+1))%HMOD1);
		h2={1};
		fwd(i,1,sz(s)+1)
			h2.pb((h2[i-1]+p2[i-1]*(s[i-1]-'a'+1))%HMOD2);
	}
	ll get(int l,int r){
		ll hsh1=(h1[r]+HMOD1-h1[l])%HMOD1*p1[sz(s)-l]%HMOD1;
		ll hsh2=(h2[r]+HMOD2-h2[l])%HMOD2*p2[sz(s)-l]%HMOD2;
		return hsh1+(hsh2<<32);
	}
};
