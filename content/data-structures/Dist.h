/**
 * Author: Arthur Botelho
 * Description: Disjoint Sparse Table
 * Requires Monoid (op, id)
 * Time: O(\log N)
 * Memory: O(N \log N)
 * Status: not tested
 */

template<class S>
struct DiST{ using T = S::T;
	int n, h; vector<vector<T>> t;
	int lg(signed x){return __builtin_clz(1)-__builtin_clz(x);}
	DiST(vector<T> v): n(sz(v)), h(lg(n)){
		if (n != (1<<h))n = 1<<(++h);
		t.assign(h, vector<T>(n)); v.resize(n, S::id);
		for(int d = 0, s = 1; d < h; d++, s *= 2)
		for(int m = s; m < n; m += 2*s){ 
			t[d][m] = v[m]; t[d][m-1] = v[m-1];
			rep(i, m+1, m+s)t[d][i] = S::op(t[d][i-1], v[i]);
			repinv(i, m-2, m-s)t[d][i] = S::op(v[i], t[d][i+1]);
		}
	}
	T query(int l, int r){
		if (l==r)return t[0][l];
		int k = lg(l^r);
		return S::op(t[k][l], t[k][r]);
	}
};

struct MinimumMonoid{
	using T = int;
	static constexpr T id = oo;
	static T op(T a, T b){return min(a,b);}
};