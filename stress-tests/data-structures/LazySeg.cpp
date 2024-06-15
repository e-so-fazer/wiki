
/*
   Used in the following problems:
   - https://judge.yosupo.jp/submission/215300
*/

#include "../utilities/template.h"
#include "../../content/data-structures/LazySeg.h"

struct MaximumSpec {
	using S = int;
	using K = int;
	static S op(S a, S b) { return max(a, b); }
	static S update(K f, S a) { return f + a; }
	static K compose(const K f, const K g) { return f + g; }
	static S id() { return 0; }
};

int main() {
	rep(n,1,10) {
		vi v(n, MaximumSpec::id());
		LazySeg<MaximumSpec> tr(v);
		rep(it,0,1000000) {
			int i = rand() % (n+1), j = rand() % (n+1);
			int x = rand() % (n+2);

			if (i > j) swap(i, j);
			int r = rand() % 100;

			if (r < 30) {
				int ma = MaximumSpec::id();
				rep(k,i,j) ma = max(ma, v[k]);
				assert(ma == tr.query(i,j));
			}
			else {
				rep(k,i,j) v[k] += x;
				tr.update(i, j, x);
			}
		}
	}
	cout<<"Test passed!"<<endl;
	return 0;
}
