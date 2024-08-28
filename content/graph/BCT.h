/**
 * Author: Ruan Petrus
 * Description: Constructs biconnected component tree 
 * Time: O(V+E)
 * Memory: O(V+E)
 * Status: not yet tested
  */
/*
  Observations:
	* Be careful with vertices without edges.
*/

struct Bcc {
	int n;
	vector<vector<pair<int, int>>> g;
	vector<pair<int, int>> edges;
	vi tin, st, art, comp;
	int dfstime = 0, stid = 0;

	vector<vi> bcc, tree;

	Bcc(int _n) : n(_n), g(n), tin(n), art(n), comp(n) {}

	void add_edge(int a, int b) {
		g[a].eb(b, sz(edges));
		g[b].eb(a, sz(edges));
		edges.eb(a, b);
	}

	int dfs(int a, int p) {
		tin[a] = ++dfstime;
		int top = tin[a];
		bool child = false;
		for (auto [b, e]: g[a]) {
			if (tin[b]) {
				top = min(top, tin[b]);
				if (tin[b] < tin[a]) {
					st.pb(e);
				}
			}
			else {
				int si = sz(st);
				int up = dfs(b, e);
				top = min(top, up);
				if (up > tin[a]) { /*e is a bridge */}
				if (up >= tin[a]) {
					st.pb(e);
					bcc.pb(vi(st.begin() + si, st.end()));
					st.resize(si);

					if (p == -1) art[a] += child;
					else art[a]++;
					child = true;
				}
				else if (up < tin[a]) st.pb(e);
			}
		}
		return top;
	}

	void build() {
		rep(a, 0, n) if (!tin[a]) dfs(a, -1);

		tree.resize(n + sz(bcc));
		rep(i, 0, sz(bcc)) {
			for (int eid: bcc[i]) {
				auto [a, b] = edges[eid];
				if (art[a] && (empty(tree[a]) || tree[a].back() != n+i)) tree[a].pb(n+i), tree[n+i].pb(a);
				if (art[b] && (empty(tree[b]) || tree[b].back() != n+i)) tree[b].pb(n+i), tree[n+i].pb(b);
				comp[a] = comp[b] = n + i;
			}
		}
		rep(i, 0, n) if (art[i]) comp[i] = i;
	}
};

