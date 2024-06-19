
/*
   Used in the following problems:
   - https://codeforces.com/problemset/problem/713/D
   - https://cses.fi/problemset/task/1647
*/

#include "../utilities/template.h"
#include "../../content/data-structures/Psum.h"

struct SG {//Sum Group
	using T = int;
	static constexpr T id = 0;
	static T op(T a, T b) { return a+b; }
	static T inv(T a){return -a;}
};

int main() {
	rep(n, 2, 5){
		Psum<1, SG> s1(n);
		Psum<2, SG> s2(n,n);
		Psum<3, SG> s3(n,n,n);
		vector<int> v1(n, 0);
		vector<vector<int>> v2(n, vector<int>(n, 0));
		vector<vector<vector<int>>> v3(n, vector<vector<int>>(n, vector<int>(n, 0)));
		rep(i, 0, n){
			int x = rand()%n;
			v1[i] = x; s1.set(x, i);
			rep(j, 0, n){
				int y = rand()%n;
				v2[i][j] = y; s2.set(y, i, j);
				rep(k, 0, n){
					int z = rand()%n;
					v3[i][j][k] = z; s3.set(z, i, j, k);
				}
			}
		}
		s1.init(); s2.init(); s3.init();
		rep(a, 0, n){
		rep(b, a, n){
			int r1=0; rep(i,a,b+1)r1+=v1[i];
			assert(s1.query(a, b)==r1);
		rep(c, 0, n){
		rep(d, c, n){
			int r2=0; rep(i,a,b+1)rep(j,c,d+1)r2+=v2[i][j];
			assert(s2.query(a,b,c,d)==r2);
		rep(e, 0, n){
		rep(f, e, n){
			int r3=0; rep(i,a,b+1)rep(j,c,d+1)rep(k,e,f+1)r3+=v3[i][j][k];
			assert(s3.query(a,b,c,d,e,f)==r3);
		}}}}}}
	}
	cout<<"Test passed!"<<endl;
	return 0;
}
