//	How far to precompute inverses
#define TS 20000001

typedef long long LL;

const LL M=1000000007;

int inv[TS+1];

int calc_inv(int l){
	if(l<=TS) return inv[l];
	return (M-M/l)*calc_inv(M%l)%M;
}

void precompute(int N){
	inv[1]=1;
	for(int i=2;i<N;++i)
		inv[i]=calc_inv(i);
}
