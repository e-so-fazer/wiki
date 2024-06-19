
/*
   Used in the following problems:
   - https://codeforces.com/problemset/problem/713/D
   - https://cses.fi/problemset/task/1647
*/

#include "../utilities/template.h"
#include "../../content/data-structures/SparseTable.h"

struct MIM {//Maximum Idempotent Monoid
	using T = int;
	static constexpr T id = 0;
	static T op(T a, T b) { return max(a, b); }
};

int main() {
	rep(n, 2, 5){
		SpTable<1, MIM> sp1(n);
		SpTable<2, MIM> sp2(n, n);
		SpTable<3, MIM> sp3(n, n, n);
		vector<int> v1(n, 0);
		vector<vector<int>> v2(n, vector<int>(n, 0));
		vector<vector<vector<int>>> v3(n, vector<vector<int>>(n, vector<int>(n, 0)));
		rep(i, 0, n){
			int x = rand()%n;
			v1[i] = x; sp1.set(x, i);
			rep(j, 0, n){
				int y = rand()%n;
				v2[i][j] = y; sp2.set(y, i, j);
				rep(k, 0, n){
					int z = rand()%n;
					v3[i][j][k] = z; sp3.set(z, i, j, k);
				}
			}
		}
		sp1.init(); sp2.init(); sp3.init();
		rep(a, 0, n){
		rep(b, a, n){
			int r1=0; rep(i,a,b+1)r1=max(r1,v1[i]);
			assert(sp1.query(a, b)==r1);
		rep(c, 0, n){
		rep(d, c, n){
			int r2=0; rep(i,a,b+1)rep(j,c,d+1)r2=max(r2,v2[i][j]);
			assert(sp2.query(a,b,c,d)==r2);
		rep(e, 0, n){
		rep(f, e, n){
			int r3=0; rep(i,a,b+1)rep(j,c,d+1)rep(k,e,f+1)r3=max(r3,v3[i][j][k]);
			assert(sp3.query(a,b,c,d,e,f)==r3);
		}}}}}}
	}
	cout<<"Test passed!"<<endl;
	return 0;
}
