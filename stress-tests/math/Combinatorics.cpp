#include "../utilities/template.h"
#include "../../content/math/Combinatorics.h"

/*
   Used in the following problems:

   - https://codeforces.com/contest/1946/problem/E
*/

int main() {
	const int mxn = 10, mx=1e6, mod=1e9+7;
	vector<ll> fact(mxn,1); rep(i, 1, mxn)fact[i] = fact[i-1]*(ll)i;
	Combinatorics<mod> comb(mx);
	rep(i, 0, mxn){
		rep(j, 0, i+1){
			//cout << comb.choose(i, j) << ' ' << (fact[i]/(fact[j]*fact[i-j])) << endl;
			assert(comb.choose(i, j)==(fact[i]/(fact[j]*fact[i-j])));
		}
	}
	cout << "Test passed!" << endl; return 0;
}
