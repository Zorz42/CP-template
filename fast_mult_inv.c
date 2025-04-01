//	How far to precompute inverses
#define TS 20000001

typedef long long LL;

const LL M=1000000007;

int inv[TS+1];

int calc_inv(int l){
	if(l<=TS) return inv[l];
	return (M-M/l)*calc_inv(M%l)%M;
}

void precompute(){
	inv[1]=1;
	for(int i=2;i<=TS;++i){
		inv[i]=(M-M/i)*inv[M%i]%M;
		if(inv[i]<0) inv[i]+=M;
	}
}
