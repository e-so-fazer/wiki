#include "../utilities/template.h"

/*
   Used in the following problems:

   - https://judge.yosupo.jp/problem/point_add_range_sum
*/

static unsigned RA = 1231231;
int ra() {
	RA *= 574841;
	RA += 14;
	return RA >> 1;
}

#include "../../content/data-structures/SegTree.h"

// https://en.wikipedia.org/wiki/Dihedral_group_of_order_6
const int lut[6][6] = {
	{0, 1, 2, 3, 4, 5},
	{1, 0, 4, 5, 2, 3},
	{2, 5, 0, 4, 3, 1},
	{3, 4, 5, 0, 1, 2},
	{4, 3, 1, 2, 5, 0},
	{5, 2, 3, 1, 0, 4}
};

struct nonabelianSpec {
	using S = int; using K = int;
	static S op(S a, S b) { return lut[a][b]; }
	static K update(K f, S a) { return f; }
	static S id() { return 0; }
};

struct maximumSpec {
	using S = int; using K = int;
	static S op(S a, S b) { return max(a, b); }
	static K update(K f, S a) { return f; }
	static S id() { return 0; }
};

int main() {
	rep(n,1,10) {
		vi v(n, maximumSpec::id());
		SegTree<maximumSpec> tr(v);
		rep(it,0,1000000) {
			int i = rand() % (n+1), j = rand() % (n+1);
			int x = rand() % (n+2);

			int r = rand() % 100;
			if (r < 30) {
				int ma = maximumSpec::id();
				rep(k,i,j) ma = max(ma, v[k]);
				assert(ma == tr.query(i,j));
			}
			else {
				i = min(i, n-1);
				tr.update(i, x);
				v[i] = x;
			}
		}
	}

	rep(n,1,10) {
		vi v(n);
		SegTree<nonabelianSpec> tr(v);
		rep(it,0,1000000) {
			int i = rand() % (n+1), j = rand() % (n+1);
			int x = rand() % 6;

			int r = rand() % 100;
			if (r < 30) {
				int ma = 0;
				rep(k,i,j) ma = lut[ma][v[k]];
				assert(ma == tr.query(i,j));
			}
			else {
				i = min(i, n-1);
				tr.update(i, x);
				v[i] = x;
			}
		}
	}

	cout<<"Test passed!"<<endl;
	return 0;
}
