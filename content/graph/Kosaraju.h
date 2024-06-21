/**
 * Author: Ruan Petrus
 * Description: Kosaraju
 * Time: O(n + m) query, O(n + m) build
 * Memory: O(n)
 * Status: not yet tested
 */

struct Kosaraju {
	int n;
	vector<vector<int>> g, rg;
	vector<bool> vis;
	vector<int> id;
	vector<vector<int>> dag, comp;
	int cc = 0;
	vector<int> S;

	Kosaraju(int _n) 
		: n(_n), g(n), rg(n), vis(n), id(n) {}

	void add_edge(int a, int b) {
		g[a].eb(b);
		rg[b].eb(a);
	}
	void dfs(int a) {
		vis[a] = true;
		for (auto b: g[a]) if (!vis[b]) dfs(b);
		S.eb(a);
	}
	void scc(int a, int c) {
		vis[a] = true;
		id[a] = c;
		for (auto b: rg[a]) if (!vis[b]) scc(b, c);
	}
	void run() {
		rep(a, 0, n) if (!vis[a]) dfs(a);
		fill(all(vis), 0);
		reverse(all(S));
		for (auto a: S) if (!vis[a]) scc(a, cc++);

		dag.resize(cc); comp.resize(cc);
		vector<pair<int, int>> edges;
		rep(a, 0, n) {
			comp[id[a]].eb(a);
			for (int b: g[a]) if (id[a] != id[b]) edges.eb(id[a], id[b]);
		}
		sort(all(edges));
		edges.erase(unique(all(edges)), edges.end());
		for (const auto & [a, b]: edges) dag[a].eb(b);
	}
};

