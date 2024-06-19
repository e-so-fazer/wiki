
/*
   Used in the following problems:
   - https://judge.yosupo.jp/submission/215300
*/

#include "../utilities/template.h"
#include "../../content/data-structures/MultiDSegTree.h"

struct MM {//Maximum Monoid
	using T = int;
	static constexpr T id = 0;
	static T op(T a, T b) { return max(a, b); }
};

int main() {
	rep(n, 2, 5){
		SegTree<1, MM> s1(n);
		SegTree<2, MM> s2(n, n);
		SegTree<3, MM> s3(n, n, n);
		vector<int> v1(n, 0);
		vector<vector<int>> v2(n, vector<int>(n, 0));
		vector<vector<vector<int>>> v3(n, vector<vector<int>>(n, vector<int>(n, 0)));
		rep(a, 0, n){
			int b = rand()%n;
			if (b%2 or b<a){
				s1.update(b, a); v1[a] = b; b=max(b,a);
			}
			else{
				int r1=0; rep(i,a,b+1)r1=max(r1,v1[i]);
				assert(s1.query(a, b)==r1);
			}
		rep(c, 0, n){
			int d = rand()%n;
			if (d%2 or d<c){
				s2.update(d, a, c); v2[a][c] = d; d = max(d, c);
			}
			else{
				int r2=0; rep(i,a,b+1)rep(j,c,d+1)r2=max(r2,v2[i][j]);
				assert(s2.query(a,b,c,d)==r2);
			}
		rep(e, 0, n){
			int f = rand()%n;
			if (f%2 or f<c){
				s3.update(f, a, c, e); v3[a][c][e] = f; f = max(f, e);
			}
			else{
				int r3=0; rep(i,a,b+1)rep(j,c,d+1)rep(k,e,f+1)r3=max(r3,v3[i][j][k]);
				assert(s3.query(a,b,c,d,e,f)==r3);
			}
		}}}
	}
	cout<<"Test passed!"<<endl;
	return 0;
}
