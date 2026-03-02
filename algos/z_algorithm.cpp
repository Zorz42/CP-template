//	z[i] pove, da se z[i] znakov zacensi z i-tim ujemajo s prvimi z[i] znaki stringa s.
vi z_function(string s){
	vi z(sz(s));
	int l=0,r=0;
	fwd(i,1,sz(s)){
		if(i<r)
			z[i]=min(r-i,z[i-l]);
		while(i+z[i]<sz(s)&&s[z[i]]==s[i+z[i]])
			z[i]++;
		if(i+z[i]>r)
			l=i,r=i+z[i];
	}
	return z;
}
