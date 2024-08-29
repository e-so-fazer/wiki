/**
 * Author: Ruan Petrus
 * Description: Sqrt Decompostion
 * Time: O(n) build, O(sqrt(n)) queries
 * Memory: O(n)
 * Status: not yet tested
 */

struct SqrtDecomp {
	using K = ll; // single element information
	using T = ll; // block information
	int n, bsz, n_block;
	vector<T> v;
	vector<int> id;
	vector<K> block;

	SqrtDecomp(const vector<T> & x): n(sz(x)), v(x), id(n) {
		bsz = sqrt(n) + 1;
		n_block = (n + bsz - 1) / bsz; // ceil(n, bsz)

		rep(i, 0, n) id[i] = i / bsz;

		// Add information to block
		block = vector<K>(n_block, oo);
		rep(i, 0, n) block[id[i]] = min(block[id[i]], v[i]);
	}

	void update(int idx, ll x) { // Update set idx to x
		int bid = id[idx];
		block[bid] = oo;
		v[idx] = x;
		rep(i, bid * bsz, min((bid+1)*bsz, n)) block[bid] = min(block[bid], v[i]);
	}

	ll query(int l, int r) { // Query of min in interval [l, r]
		assert(l <= r); // Or return id;

		ll ans = oo;
		auto sblk = [&](int bid, int flag) { // flag [left, right, both]
			rep(i, max(l, bid*bsz), min((bid+1)*bsz, r+1)) ans = min(ans, v[i]);
		};

		auto allblk = [&](int bid) { // Solve entire block
			ans = min(ans, block[bid]);
		};

		if (id[l] == id[r]) {
			sblk(id[l], 2);
		}
		else {
			sblk(id[l], 0);
			rep(i, id[l]+1, id[r]) allblk(i);
			sblk(id[r], 1);
		}
		return ans;
	}
};

