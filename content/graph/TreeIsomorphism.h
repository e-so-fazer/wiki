/**
 * Author: Ruan Petrus
 * Description: Computes Hash of a Tree, can be rooted or unrooted
 * Time: O(N)
 * Status: not stress-tested
 */

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> dist(0, (ll)1e18);

const int mxH = 2; // How many random numbers to use as a Hash
using Hash = array<ll, mxH>;
using UHash = pair<Hash, Hash>;

struct TreeHasher{
	map<vector<Hash>, Hash> table;
	using Tree = vector<vector<int>>;

	void calc_sz(int a, int p, const Tree & g, vector<int> & tam) {
		tam[a] = 1;
		for (int b: g[a]) if (b != p) {
			calc_sz(b, a, g, tam);
			tam[a] += tam[b];
		}
	}
	pair<int, int> centroid(int a, int p, const Tree & g, const vector<int> & tam, const int target) {
		for (int b: g[a]) if (b != p) {
			if (tam[b]*2 > target) return centroid(b, a, g, tam, target);
		}
		pair<int, int> ans = {a, a};
		for (auto b: g[a]) if (b != p) 
			if (tam[b]*2 > target-1) ans.second = b;
		return ans;
	}
	Hash hash_vec(const vector<Hash> & vs) {
		auto it = table.find(vs);
		if (it != table.end()) return it->second;
		else {
			Hash ans; rep(i, 0, mxH) ans[i] = dist(rng);
			return table[vs] = ans;
		}
	}
	Hash rooted_tree(int a, int p, const Tree & g) {
		vector<Hash> childs;
		for (int b: g[a]) if (b != p) {
			childs.pb(rooted_tree(b, a, g));
		}
		sort(all(childs));
		return hash_vec(childs);
	}
	UHash unrooted_tree(int root, const Tree & g, const vector<int> & tam) {
		auto c = centroid(root, root, g, tam, tam[root]);
		Hash h1 = rooted_tree(c.first, c.first, g);
		if (c.first == c.second) return {h1, h1};
		else {
			Hash h2 = rooted_tree(c.second, c.second, g);
			UHash ans = {min(h1, h2), max(h1, h2)};
			return ans;
		}
	}
	UHash unrooted_tree(int root, const Tree & g) {
		int n = sz(g);
		vector<int> tam(n);
		calc_sz(root, root, g, tam);
		return unrooted_tree(root, g, tam);
	}
	UHash unrooted_tree(const Tree & g) {
		return unrooted_tree(0, g);
	}
};

