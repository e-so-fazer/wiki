#include "../utilities/template.h"
#include "../../content/math/Mint.h"

/*
   Used in the following problems:
   - https://codeforces.com/contest/1946/problem/E
*/

template<int mod> void mod_test(){
	auto add = [&](int a, int b)->int{return (a+b)%mod;};
	auto sub = [&](int a, int b)->int{return (a+mod-b)%mod;};
	auto mul = [&](int a, int b)->int{return ((ll)a*(ll)b)%mod;};
	auto fexp = [&](int a, int b)->int{
		int res = 1;
		for(;b;a=mul(a,a),b>>=1)if(b&1)res=mul(res,a);
		return res;
	};
	auto div = [&](int a, int b)->int{return mul(a, fexp(b, mod-2));};
	int tests = 100;
	using mint = Z<mod>;
	while(tests--){
		int a = rand()%mod;
		int b = rand()%mod; if (not b)b++;
		assert(add(a,b)==(int)(mint(a)+mint(b)));
		assert(sub(a,b)==(int)(mint(a)-mint(b)));
		assert(mul(a,b)==(int)(mint(a)*mint(b)));
		if (mod%2)assert(div(a,b)==(int)(mint(a)/mint(b)));
	}
}

int main() {
	mod_test<998244353>();
	mod_test<1000000007>();
	mod_test<1000000009>();
	mod_test<7>();
	mod_test<3>();
	cout << "Test Passed!\n";
}
