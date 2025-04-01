//	How far to precompute inverses
#define TS 20000001

typedef long long LL;

const LL M=1000000007;

int inv[TS+1];

int calc_inv(int l){
	if(l<=TS) return inv[l];
	return (M-M/l)*calc_inv(M%l)%M;
}
