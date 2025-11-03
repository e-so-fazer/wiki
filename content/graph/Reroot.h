/**
 * Author: Ruan Petrus
 * Description: Computes reroot of a associative operation S op(S a, S b)
 * Time: O(N)
 * Status: not stress-tested
 */

template<typename LS>
struct Reroot {
	using S = typename LS::S;
	using K = typename LS::K;

	vector<vector<int>> g;
	vector<S> dp;
	vector<K> ks;

	Reroot(int n, const vector<K> & v): g(n), dp(n, LS::id()), ks(v) {}

	void add_edge(int a, int b) {
		g[a].pb(b); g[b].pb(a);
	}
	void dfs(int a, int p) {
		for (int b: g[a]) if (b != p) {
			dfs(b, a);
			dp[a] = LS::op(dp[a], dp[b]);
		}
		dp[a] = LS::finalize(ks[a], dp[a]);
	}
	void reroot(int a, int p) {
		vector<S> root_dp;
		for (int b: g[a])
			root_dp.pb(dp[b]);

		vector<S> ldp(sz(root_dp), LS::id());
		vector<S> rdp = ldp;
		rep(i, 1, sz(root_dp)) ldp[i] = LS::op(ldp[i-1], root_dp[i-1]);
		for (int i = sz(root_dp)-2; i >= 0; i--) 
			rdp[i] = LS::op(root_dp[i+1], rdp[i+1]);

		rep(i, 0, sz(g[a])) if (g[a][i] != p) {
			dp[a] = LS::finalize(ks[a], LS::op(ldp[i], rdp[i]));
			reroot(g[a][i], a);
		}
		dp[a] = LS::id();
		for (auto x: root_dp) dp[a] = LS::op(dp[a], x);
		dp[a] = LS::finalize(ks[a], dp[a]);
	}
	void run() {
		dfs(0, 0);
		reroot(0, 0);
	}
};

struct Spec {
	using K = int;
	using S = int;
	static constexpr S op(S a, S b) {
		return max(a, b);
	}
	static constexpr S finalize(K p, S a) {
		return max(p, a + 1);
	}
	static constexpr S id() {
		return -1;
	}
};
