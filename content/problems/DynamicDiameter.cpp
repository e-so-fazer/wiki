/**
 * Author: Ruan Petrus
 * Description: Given a weighted tree of n vertices, and q queries updating the weight
 * of the edges, find the diameter of the tree after each query ONLINE
   After each query count how many bridges are in the graph
 * Time: O(max(n, q) * log²n)
 * Status: stress-tested
 */


#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define pb push_back
#define eb emplace_back
#define all(x) begin(x), end(x)
#define debug(x) cout << #x << ": " << (x) << endl
#define rep(i, a, b) for (int i = a; i < (int)(b); i++)
#define irep(i, a, b) for (int i = a; i >= (int)(b); i--)

#define inbounds(x, l, r) ((l) <= (x) && (x) <= (r))
#define L0(res...) [&](){ return res; }
#define L1(res...) [&](auto const & x){ return res; }
#define L2(res...) [&](auto const & x, auto const& y){ return res; }
#define sz(x) (int)x.size()

template<class T> inline void chmin(T & a, const T b){ if (a > b) a = b; }
template<class T> inline void chmax(T & a, const T b){ if (a < b) a = b; }

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long long ll;
typedef long double ld;

const ll oo = 0x3f3f3f3f3f3f3f3f;

/**
 * Author: Ruan Petrus
 * Description: Iterative Lazy SegTree
 * Can be changed by modifying Spec
 * Time: O(\log N)
 * Status: stress-tested
 */

template<typename Spec>
struct LazySeg {
	using LS = Spec;
	using S = typename LS::S;
	using K = typename LS::K;
	int n;
	vector<S> seg;
	vector<K> lazy;
	vector<bool> has_lazy;

	LazySeg() {}

	LazySeg(int _n): LazySeg(vector<S>(_n, LS::id())) {}
	
    LazySeg(vector<S> v) : n(sz(v)), seg(2*n) , lazy(n), has_lazy(n) {
		rep(no, 0, n) seg[no+n] = v[no];
		for (int no = n-1; no >= 1; no--) pull(no);
	}

	S query(int l, int r) { // [l, r)
		l += n;
		r += n;
		push_to(l); push_to(r-1);
		S vl = LS::id(), vr = LS::id();
		while(l < r) {
			if (l & 1) vl = LS::op(vl, seg[l++]);
			if (r & 1) vr = LS::op(seg[--r], vr);
			l >>= 1; r >>= 1; 
		}
		return LS::op(vl, vr);
	}

	void update(int l, int r, K val) {
		l += n;
		r += n;
		push_to(l); push_to(r-1);
		int lo = 1, ro = 1; 
		while(l < r) {
			if (l & 1) lo = max(lo, l), apply(l++, val);
			if (r & 1) ro = max(ro, r), apply(--r, val);
			l >>= 1; r >>= 1;
		}
		pull_from(lo);
		pull_from(ro-1);
	}

	void apply(int no, K val) {
		seg[no] = LS::update(val, seg[no]);
		// seg[no] = LS::update(val, seg[no], lx[no], rx[no]);

		if (no < n) {
			if (has_lazy[no]) lazy[no] = LS::compose(val, lazy[no]);
			else lazy[no] = val;
			has_lazy[no] = true;
		}
	}

	void pull_from(int no) {
		while(no > 1) no >>= 1, pull(no);
	}

	void pull(int no) {
		seg[no] = LS::op(seg[no*2], seg[no*2+1]);
	}

	void push_to(int no) {
		int h = 0; int p2 = 1;
		while(p2 < no) p2 *= 2, h++;
		for (int i = h; i >= 1; i--) push(no >> i);
	}

	void push(int no) {
		if (has_lazy[no]) {
			apply(no*2, lazy[no]);
			apply(no*2+1, lazy[no]);
			has_lazy[no] = false;
		}
	}
};

/**
 * Author: Ruan Petrus
 * Description: Iterative SegTree
 * Can be changed by modifying Spec
 * Time: O(\log N)
 * Status: stress-tested
 */

template<typename LS>
struct SegTree {
	using S = typename LS::S;
	using K = typename LS::K;
	int n;
	vector<S> seg;

	SegTree(int _n)
		: n(_n), seg(2*n, LS::id()) {}

	void update(int no, K val) {
		no += n;
		seg[no] = LS::update(val, seg[no]);
		while (no > 1) no /= 2, seg[no] = LS::op(seg[no*2], seg[no*2+1]);
	}

	S query(int l, int r) { // [l, r)
		S vl = LS::id(), vr = LS::id();
		for (l += n, r += n; l < r; l /= 2, r /= 2) {
			if (l & 1) vl = LS::op(vl, seg[l++]);
			if (r & 1) vr = LS::op(seg[--r], vr);
		}
		return LS::op(vl, vr);
	}
};

struct Spec {
	using S = ll;
	using K = ll;
	static S op(S a, S b) { return max(a, b); }
	static S update(K f, S a) { return f + a; }
	static K compose(const K f, const K g) { return f + g; }
	static S id() { return 0; }
};

struct AnsSpec {
	using S = ll;
	using K = ll;
	static S op(S a, S b) { return max(a, b); }
	static S update(K f, S a) { return f; }
	static S id() { return 0; }
};

const int mxN = 1e5 + 5;
vector<tuple<int, ll, int>> g[mxN];
multiset<ll> V[mxN];
vector<tuple<int, int, int>> E[mxN];
ll W[mxN];

SegTree<AnsSpec> ans(mxN);

int ssz[mxN], tin[mxN], tout[mxN];
bool used[mxN];
int dfstime = 0;

map<int, pair<int, int>> T[mxN];

LazySeg<Spec> seg[mxN];

int dfs_sz(int a, int p = -1) {
	ssz[a] = 1;
	for (auto [b, w, eid]: g[a]) if (b != p && !used[b]) {
		ssz[a] += dfs_sz(b, a);
	}
	return ssz[a];
}

int centroid(int a, int x, int p = -1) {
	for (auto [b, w, eid]: g[a]) if (b != p && !used[b]) {
		if (ssz[b] * 2 > x) return centroid(b, x, a);
	}
	return a;
}

void dfs(int a, int p, int c, int ba, ll d) {
	tin[a] = dfstime++;
	seg[c].update(tin[a], tin[a]+1, d);
	for (auto [b, w, eid]: g[a]) if (b != p && !used[b]) {
		int nba = (ba == -1 ? b : ba);
		E[eid].eb(c, nba, b);
		dfs(b, a, c, nba, d + w);
	}
	tout[a] = dfstime;
	T[c][a] = {tin[a], tout[a]};
}

void centroid_decomp(int a) {
	int c = centroid(a, dfs_sz(a));
	used[c] = true;

	dfstime = 0;
	seg[c] = LazySeg<Spec>(ssz[a]);
	dfs(c, c, c, -1, 0);

	V[c].insert(0);
	V[c].insert(0);

	for (auto [b, w, eid]: g[c]) if (!used[b]) {
		auto [l, r] = T[c][b];
		V[c].insert(seg[c].query(l, r));
	}

	ll me = *prev(V[c].end()) + *prev(prev(V[c].end()));
	ans.update(c, me);

	for (auto [b, w, eid]: g[c]) if (!used[b]) {
		centroid_decomp(b);
	}
}

void update(int eid, ll c) {
	ll diff = c - W[eid];
	W[eid] = c;

	for (auto [c, ba, b]: E[eid]) {
		auto [l, r] = T[c][ba];
		V[c].erase(V[c].find(seg[c].query(l, r)));

		auto [lx, rx] = T[c][b];
		seg[c].update(lx, rx, diff);

		V[c].insert(seg[c].query(l, r));

		ll res = *prev(V[c].end()) + *prev(prev(V[c].end()));
		ans.update(c, res);
	}
}

void solve() {
	int n, q;
	cin >> n >> q;
	ll w; cin >> w;
	rep(i, 0, n-1) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		ll c; cin >> c;
		g[a].eb(b, c, i);
		g[b].eb(a, c, i);
		W[i] = c;
	}
	centroid_decomp(0);
	ll last = 0;
	while(q--) {
		int dj; cin >> dj;
		int d = (dj + last) % (n-1);
		ll cj; cin >> cj;
		ll c = (cj + last) % w;

		update(d, c);

		last = ans.query(0, n);
		cout << last << endl;
	}
}

int32_t main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1;
	// cin >> t;
	for (int i = 0; i < t; i++) {
		solve();
	}
	return 0;
}
