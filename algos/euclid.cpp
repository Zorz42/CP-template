// gcd(a,b,x,y): returns gcd(a,b) and sets x,y so that a*x+b*y=gcd(a,b)
ll gcd(ll a,ll b,ll&x,ll&y){
	if(!b)return x=1,y=0,a;
	ll d=gcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}
