#include "../utilities/template.h"
#include "../../content/math/LinearDiophantineEquation.h"

/*
   Used in the following problems:

   - https://atcoder.jp/contests/abc340/tasks/abc340_f
*/

int main() {
	const int mxX = 200;
	rep(a, -mxX, mxX) rep(b, -mxX, mxX) rep(c, -mxX, mxX) {
		if (a == 0 && b == 0) continue;
		auto [can, x, y, g] = find_any_solution(a, b, c);
		if (can) {
			assert(x*a + b*y == c);
		}
	}
	cout<<"Test passed!"<<endl;
	return 0;
}
