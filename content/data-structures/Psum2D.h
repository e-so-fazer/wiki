/**
 * Author: Ruan Petrus
 * Description: Psum 2D with queries in modular space
 * Can be changed by modifying Spec
 * Time: O(\log N)
 * Status: stress-tested
 */

template<typename S>
struct Psum2d {
	int n, m;
	vector<vector<S>> v;
	Psum2d() {}

	template<typename T>
	Psum2d(const vector<vector<T>> & a) : n(sz(a)), m(sz(a[0])), v(n + 1, vector<S>(m + 1, 0)) {
		rep(i, 0, n) rep(j, 0, m) {
			v[i+1][j+1] = a[i][j] + v[i+1][j] + v[i][j+1] - v[i][j];
		}
	}

	S query(int x1, int y1, int x2, int y2) { // [x1, x2), [y1, y2)
		return v[x2][y2] - v[x2][y1] - v[x1][y2] + v[x1][y1];
	}

	S query2mod(int x1, int y1, int x2, int y2) { // [x1, x2), [y1, y2)
		if (x1 >= x2) {
			return query2mod(x1, y1, n, y2) + query2mod(0, y1, x2, y2);
		}
		else if (y1 >= y2) {
			return query2mod(x1, y1, x2, m) + query2mod(x1, 0, x2, y2);
		}
		else return query(x1, y1, x2, y2);
	}

	S queryInfmod(ll x1, ll y1, ll x2, ll y2) { // [x1, x2), [y1, y2)
		ll szx = x2 - x1;
		int sx  = x1 % n;
		int fx  = x2 % n;

		ll szy = y2 - y1;
		int sy = y1 % m;
		int fy = y2 % m;

		ll vx = szx/n;
		ll vy = szy/m;
		S ans = 0;

		ans += vx  * vy * query2mod(0, 0, n, m);
		ans += vx * query2mod(0, sy, n, fy+1);
		ans += vy * query2mod(sx, 0, fx+1, m);
		ans += query2mod(sx, sy, fx+1, fy+1);

		return ans;
	}
};
