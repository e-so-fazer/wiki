#include "../utilities/template.h"
#include "../../content/string/Zfunction.h"

/*
   Used in the following problems:
   - https://codeforces.com/contest/346/problem/B
   - https://cses.fi/problemset/task/2107/
*/

int main() {
	string s = "abacaba";
	vi v = {1, 2, 1, 9, 1, 9, 1};
	vi zs = zfunction(s);
	vi zv = zfunction(v);
	rep(i, 0, sz(s)){
		string suf = s.substr(i, sz(s)-i);
		int best = 0;
		rep(j, 0, sz(s)-i){
			if (suf.substr(0, j+1)==s.substr(0, j+1))best = j+1;
		}
		assert(zs[i]==best);
	}
	auto subv = [&](vi v, int b, int s)->vi{
		vi res; rep(i, b, b+s)res.pb(v[i]);
		return res;
	};
	rep(i, 0, sz(v)){
		vi suf = subv(v, i, sz(v)-i);
		int best = 0;
		rep(j, 0, sz(v)-i){
			if (subv(suf, 0, j+1)==subv(v, 0, j+1))best = j+1;
		}
		assert(zv[i]==best);
	}
	cout << "Test passed!\n";
}
