/**
 * Author: Ruan Petrus
 * Description: Constructs two edge component tree 
 * Time: O(V+E)
 * Memory: O(V+E)
 * Status: not yet tested
  */
/*
  Observations:
	* Be careful with vertices without edges.
*/

struct Twocc {
	int n;
	vector<vector<pair<int, int>>> g;
	vector<pair<int, int>> edges;
	vi tin, st, comp, pontes;
	int dfstime = 0, stid = 0;

	vector<vi> twocc, tree;

	Twocc(int _n) : n(_n), g(n), tin(n), comp(n) {}

	void add_edge(int a, int b) {
		g[a].eb(b, sz(edges));
		g[b].eb(a, sz(edges));
		edges.eb(a, b);
	}

	int dfs(int a, int p) {
		tin[a] = ++dfstime;
		int top = tin[a];
		int si = st.size();
		st.pb(a);
		for (auto [b, e]: g[a]) if (e != p) {
			if (tin[b]) {
				top = min(top, tin[b]);
			}
			else {
				int up = dfs(b, e);
				top = min(top, up);
				if (up > tin[a]) {
					pontes.pb(e);
				}
			}
		}
		if (top == tin[a]) {
			twocc.pb(vi(st.begin() + si, st.end()));
			st.resize(si);
		}
		return top;
	}

	void build() {
		rep(a, 0, n) if (!tin[a]) dfs(a, -1);

		rep(i, 0, sz(twocc))
			for (int a: twocc[i]) comp[a] = i;

		tree.resize(sz(twocc));

		for (int eid: pontes) {
			auto [a, b] = edges[eid];
			tree[comp[a]].pb(comp[b]), tree[comp[b]].pb(comp[a]);
		}
	}
};
