/**
 * Author: Ruan Petrus
 * Description: Two sat
 * Time: O(n + m) query, O(n + m) build
 * Memory: O(n)
 * Status: not yet tested
 */

struct TwoSat{
	int n;
	vector<vector<int>> g, gi;
	vector<bool> vis;
	vector<int> vars, comp;
	vector<int> top;
	TwoSat(int _n) 
		: n(_n), g(2*n), gi(2*n), vis(2*n), vars(n, -1), comp(2*n)
	{}

	int neg(int a) {
		if (a >= n) return a-n;
		return a + n;
	}

	void add_or(int a, int b) {
		g[neg(a)].eb(b);
		g[neg(b)].eb(a);

		gi[b].eb(neg(a));
		gi[a].eb(neg(b));
	}

	void add_imp(int a, int b) {
		add_or(neg(a), b);
	}

	void add_either(int a, int b) {
		add_or(a, b);
		add_or(neg(a), neg(b));
	}

	void dfs(int a) {
		vis[a] = true;
		for (auto b: g[a]) if (!vis[b]) dfs(b);
		top.eb(a);
	}

	void idfs(int a, int c){
		vis[a] = true;
		comp[a] = c;
		for (auto b: gi[a]) if (!vis[b]) idfs(b, c);
	}

	bool sat() {
		int c = 0;
		rep(a, 0, 2*n) if (!vis[a]) dfs(a);

		fill(all(vis), 0);
		reverse(all(top));
		for(int a : top) if (!vis[a]) idfs(a, c++);

		for(int a: top){
			if (comp[a] == comp[neg(a)]) return false;

			bool is_neg = a >= n;
			if (is_neg) a = neg(a);

			if (vars[a] == -1) vars[a] = is_neg;
		}

		return true;
	}
};
