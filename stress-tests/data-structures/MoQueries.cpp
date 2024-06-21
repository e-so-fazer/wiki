
/*
   Used in the following problems:
*/

#include "../utilities/template.h"
#include "../../content/data-structures/MoQueries.h"

int main() {
	rep(n,1,10) {
		vector<pii> queries;
		rep(it,0,100000) {
			int i = rand() % (n), j = rand() % (n);
			if (i > j) swap(i, j);
			queries.eb(i, j);
		}
		vector<int> values(n);
		rep(i, 0, n) values[i] = rand() % (n+5);
		auto res = mo(queries, values);
		for (int i = 0; i < sz(queries); i++) {
			auto [l, r] = queries[i];
			int val = 0;
			rep(k, l, r) val += values[k];
			assert(val == res[i]);
		}

	}
	cout<<"Test passed!"<<endl;
	return 0;
}
