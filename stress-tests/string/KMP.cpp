#include "../utilities/template.h"
#include "../../content/string/KMP.h"

/*
   Used in the following problems:
   - https://codeforces.com/contest/346/problem/B
   - https://cses.fi/problemset/task/2107/
*/

int main() {
	string s = "abacaba";
	vi v = {1, 2, 1, 9, 1, 9, 1};
	KMP<char> kmps(s, 'a', 26);
	KMP<int> kmpv(v, 1, 9);
	rep(i, 0, sz(s)){
		string cur = s.substr(0, i+1);
		int best = 0;
		rep(j, 0, i){
			if (cur.substr(0, j+1)==cur.substr(i-j, j+1))best = j+1;
		}
		assert(best==kmps.p[i]);
	}
	auto subv = [&](vi v, int b, int s)->vi{
		vi res; rep(i, b, b+s)res.pb(v[i]);
		return res;
	};
	rep(i, 0, sz(v)){
		vi cur = subv(v, 0, i+1);
		int best = 0;
		rep(j, 0, i){
			if (subv(cur, 0, j+1)==subv(cur, i-j, j+1))best = j+1;
		}
		assert(best==kmpv.p[i]);
	}
	rep(i, 0, sz(s)){
		string cur = s.substr(0, i);
		rep(c, 0, 26){
			cur.pb('a'+c);
			int best=0;
			rep(j, 0, i+1){
				if (cur.substr(i-j, j+1)==s.substr(0, j+1))best = j+1;
			}
			assert(best==kmps.nxt(i, 'a'+c));
			cur.pop_back();
		}
	}
	rep(i, 0, sz(v)){
		vi cur = subv(v, 0, i);
		rep(c, 0, 9){
			cur.pb(1+c);
			int best=0;
			rep(j, 0, i+1){
				if (subv(cur, i-j, j+1)==subv(v, 0, j+1))best = j+1;
			}
			assert(best==kmpv.nxt(i, 1+c));
			cur.pop_back();
		}
	}
	cout << "Test passed!\n";
}
