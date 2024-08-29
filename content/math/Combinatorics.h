/**
 * Author: Arthur Botelho
 * Description: combinatorics structure
 * Time: O(mxn)
 * Memory: O(mxn)
*/

#define mul(a, b) (((ll)a*b)%mod)
template<int mod>
int fexp(int a, int b){
	int res = 1;
	for(;b;a=mul(a,a),b>>=1)if(b&1)res=mul(res,a);
	return res;
}
template<int mod>
struct Combinatorics{
	vi f, fi;
	Combinatorics(int mxn):f(mxn),fi(mxn){
		f[0] = 1; rep(i, 1, mxn)f[i]=mul(f[i-1],i);
		fi[mxn-1] = fexp<mod>(f[mxn-1], mod-2);
		for(int i=mxn-1;i>0;i--)fi[i-1] = mul(fi[i],i);
	}
	int choose(int n, int k){return mul(f[n],mul(fi[k],fi[n-k]));}
};
