/**
 * Author: Ruan Petrus
 * Description: Adds intervals and keep information about then
 * Time: O(Q * log(Q))
 * Memory: O(Q)
 * Status: not yet tested
 */

struct ColorUpdate {
	using IT  = pair<pair<int, int>, int>;
	map<int, ll> freq;
	set<IT> rgs;

	vector<set<IT>::iterator> intersect(int l, int r) { // Return all ranges that intersects with [l, r]
		vector<set<IT>::iterator> ans;
		auto it = rgs.lower_bound(pair(pair(r+1, -1), -1));
		while(it != rgs.begin()) {
			it = prev(it);
			auto [lx, rx] = it->first;
			if (rx < l) break;
			ans.pb(it);
		}
		return ans;
	}

	void add(int l, int r, int c) { // Adds a range [l, r] with color c
		auto v = intersect(l, r);
		vector<IT> to_add = {{{l, r}, c}};
		for (auto it: intersect(l, r)) {
			// Remove it information
			freq[it->second] -= it->first.second - it->first.first + 1;

			to_add.pb({{it->first.first, l-1}, it->second});
			to_add.pb({{r+1, it->first.second}, it->second});
			rgs.erase(it);
		}
		for (auto [x, c]: to_add) {
			if (x.first > x.second) continue;
			rgs.insert({x, c});

			// Add x c information
			freq[c] += x.second - x.first + 1;

		}
	}
};
