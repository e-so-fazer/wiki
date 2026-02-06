/**
 * Author: Eduardo Freire
 * Description: TODO
 * Time: TODO
 * Status: TODO
 */

#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
#define eb emplace_back
#define rep(i, a, b) for (int i = a; i < (int)(b); i++)
#define sz(x) (int)x.size()
typedef long long ll;
typedef long double ld;
struct P { ll x, y; };
 
// Line Segment
int current_x;
struct Segment {
	int idx; P p1, p2; bool is_upper;
	Segment(P p, P q, int i): idx(i), p1(p), p2(q), is_upper(p2.x < p1.x) { if (is_upper)swap(p1, p2); }
	ld get_y(ll x) const { return (ld) (p2.y - p1.y) / (p2.x - p1.x) * (x - p1.x) + p1.y; }
	tuple<ld, bool, int> get_comp() const { return {get_y(current_x), is_upper, p2.x}; }
	bool operator<(const Segment & o) const { return get_comp() < o.get_comp(); }
};
 
signed main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, q; cin >> n >> q;
	vector<vector<P>> polygons(n);
	rep(i, 0, n) {
		int k; cin >> k;
		rep(j, 0, k) {
			int x, y; cin >> x >> y;
			polygons[i].eb(x, y);
		}
	}
	vector<P> queries(q);
	rep(i, 0, q) {
		int x, y; cin >> x >> y;
		queries[i] = {x, y};
	}
	vector<tuple<int, int, int, Segment>> edges; // polygon edges
	rep(idx, 0, n) {
		const auto & v = polygons[idx];
		rep(i, 0, sz(v)) {
			int j = (i + 1) % sz(v);
			if (v[i].x == v[j].x)continue; // ignores vertical edges
			Segment seg = Segment(v[i], v[j], idx);
			edges.eb(seg.p1.x, 0, -seg.p1.y, seg);
			edges.eb(seg.p2.x, 1, -seg.p2.y, seg);
		}
	}
	rep(idx, 0, q){
		P p = queries[idx];
		P p2 = p; p2.x++; // this wont be used by the sweep line
		Segment seg = Segment(p, p2, n + idx);
		edges.eb(seg.p1.x, 0, -seg.p1.y, seg);
	}
	
	// Sweep Line
	sort(edges.begin(), edges.end());
	set<Segment> s;
	vector pai(n+q+1, n), vis(n+q, 0);
	for (auto [l, t, y, seg]: edges) {
		current_x = l;
		int i = seg.idx;
		if (t == 0) {
			if (not vis[i]) {
				vis[i] = true;
				auto it = s.upper_bound(seg);
				if (it == s.end())pai[i] = n+q;
				else if (it->is_upper)pai[i] = it->idx;
				else pai[i] = pai[it->idx];
			}
			if (i < n)s.insert(seg);
		}
		else if (i < n)s.erase(seg);
	}
	
	// depth in tree
	vector<vector<int>> g(n+q+1);
	rep(i, 0, n+q)g[pai[i]].pb(i), g[i].pb(pai[i]);
	vector h(n+q+1, -2); // plane is -1, bigger polygons are 0
	auto dfs = [&](auto rec, int v, int p) -> void {
		h[v] = h[p] + 1;
		for(int f : g[v])if (f != p)rec(rec, f, v);
	};
	dfs(dfs, n+q, n+q);
	rep(i, n, n+q)cout << h[i] << endl;
}
