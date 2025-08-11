/**
 * Author: Ruan Petrus
 * Description: Queries of deleting and adding edges. After each query count how many bridges are in the graph
 * Can be changed by modifying Spec
 * Time: O(\log N)
 * Status: stress-tested
 */

struct Twocc {
	int n;
	vector<vector<pair<int, int>>> g;
	vector<tuple<int, int, int>> edges;
	vi tin, st, comp, pontes;
	int dfstime = 0;

	vector<vi> twocc;
	vector<vector<pair<int, int>>> tree;

	Twocc(int _n) : n(_n), g(n), tin(n), comp(n) {}
	Twocc(const vector<vector<pair<int, int>>> & _g) : n(sz(_g)), g(n), tin(n), comp(n) {
	   rep(a, 0, n) for (const auto & [b, w]: _g[a]) add_edge(a, b, w);
	}

	void add_edge(int a, int b, int w) {
		g[a].eb(b, sz(edges));
		g[b].eb(a, sz(edges));
		edges.eb(a, b, w);
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
			twocc.eb(st.begin() + si, st.end());
			st.resize(si);
		}
		return top;
	}

	void build(const vector<vector<pair<int, int>>> & _g) {
		int n = sz(_g);
	   	rep(a, 0, n) for (const auto & [b, w]: _g[a]) add_edge(a, b, w);
		rep(a, 0, n) if (!tin[a]) dfs(a, -1);

		rep(i, 0, sz(twocc))
			for (int a: twocc[i]) comp[a] = i;

		tree.resize(sz(twocc));

		for (int eid: pontes) {
			auto [a, b, w] = edges[eid];
			tree[comp[a]].eb(comp[b], w), tree[comp[b]].eb(comp[a], w);
		}
	}

	void clear(int n) {
		rep(a, 0, n) g[a].resize(0);
		edges.resize(0); pontes.resize(0);
		tree.resize(0); twocc.resize(0);
		fill(tin.begin(), tin.begin() + n, 0);
		dfstime = 0;
	}
};

struct Edge {
	int l, r;
	int a, b;
};

tuple<vector<Edge>, vector<vector<pair<int, int>>>, int> compress(const Twocc & cc, vector<Edge> edges) {
	int n = sz(cc.tree);
	int out_bridges = 0;

	for (auto &e: edges) e.a = cc.comp[e.a], e.b = cc.comp[e.b];

	int vID = 0;
	vector<int> vid(n), vis(n), h(n), good(n);
	vector<vector<pair<int, int>>> vt;

	for (auto e: edges) good[e.a] = true, good[e.b] = true;

	auto dfs = [&](auto rec, int a, int p) -> int {
		vis[a] = true;
		vector<int> vs;
		for (auto [b, w]: cc.tree[a]) if (b != p) {
			h[b] = h[a] + w;
			int v = rec(rec, b, a);
			if (v != -1) vs.pb(v);
		}
		good[a] |= sz(vs) >= 2;
		int ans = -1;
		if (good[a]) {
			vid[a] = vID++; vt.eb();
			for (int b: vs) {
				vt[vid[a]].eb(vid[b], h[b] - h[a]);
			}
			ans = a;
		}
		else if (sz(vs) == 1) ans = vs[0];
		if (ans == -1) { // My edge is not relevant, i can add to answer now
			out_bridges += h[a] - h[p];
		}
		return ans;
	};
	rep(i, 0, n) if (!vis[i]) {
		int r = dfs(dfs, i, i);
		if (r != -1) { // last edges are not relevant
			out_bridges += h[r] - h[i];
		}
	}
	for (auto &e: edges) {
		e.a = vid[e.a];
		e.b = vid[e.b];
	}
	return {edges, vt, out_bridges};
}

void solve() {
	int n, k;
	cin >> n >> k;
	vector<Edge> edges;
	map<pair<int, int>, int> m;
	rep(i, 0, k) {
		string s; cin >> s;
		if (s == "ADD") {
			int a, b;
			cin >> a >> b;
			a--; b--;
			pair<int, int> p = {min(a, b), max(a,b)};
			m[p] = i;
		}
		else if (s == "DEL") {
			int a, b;
			cin >> a >> b;
			a--; b--;
			pair<int, int> p = {min(a, b), max(a,b)};
			assert(m.count(p));
			edges.pb({m[p], i, p.first, p.second});
			m.erase(p);
		}
		else assert(0);
	}
	for (auto [p, l]: m) edges.pb({l, k, p.first, p.second});
	vector<int> ans(k);
	Twocc cc(n);
	auto dv = [&](auto rec, int l, int r, const vector<Edge> & edges, 
			      const vector<vector<pair<int, int>>> & florest, int out_bridges) -> void {
		if (l+1 == r) {
			ans[l] = out_bridges;
			return;
		}
		if (l >= r) return;
		int mid = l + (r-l)/2;

		auto div = [&](int lx, int rx) {
			vector<Edge> useful;
			cc.clear(sz(florest));
			for (const auto &e : edges) {
				if (e.l <= lx && rx <= e.r) {
					cc.add_edge(e.a, e.b, 1);
				}
				else if (!(e.r <= lx || rx <= e.l)) {
					useful.pb(e);
				}
			}
			cc.build(florest);
			auto [n_edges, n_florest, n_out_bridges] = compress(cc, useful);
			rec(rec, lx, rx, n_edges, n_florest, out_bridges + n_out_bridges);
		};
		div(l, mid);
		div(mid, r);
	};
	vector<vector<pair<int, int>>> g(n);
	dv(dv, 0, k, edges, g, 0);

	for (auto x: ans) cout << x << endl;
}

