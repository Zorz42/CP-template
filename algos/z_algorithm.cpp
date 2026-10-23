// z_function(s): z[i] is the length of the longest common prefix of s and s[i..], z[0]=0
vi z_function(const string&s){
	int n=sz(s),l=0,r=0;
	vi z(n);
	fwd(i,1,n){
		if(i<r)z[i]=min(r-i,z[i-l]);
		while(i+z[i]<n&&s[z[i]]==s[i+z[i]])z[i]++;
		if(i+z[i]>r)l=i,r=i+z[i];
	}
	return z;
}
