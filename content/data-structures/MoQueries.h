/**
 * Author: Ruan Petrus
 * Description: Solve queries offline
 * Can be changed by modifying Spec
 * Time: $O(n * \sqrt(q))$
 * Status: not stress_tested
 */

template<typename LS>
void mo(LS & v, vector<pii> Q) { // Queries in Q are [l, r)
	int L = 0, R = 0, blk = 350; // N/sqrt (Q)

	vi s(sz(Q));
	auto K = [&](pii x) {return pii(x.first/blk, x.second ^ -(x.first/blk & 1)); };
	iota(all(s), 0);
	sort(all(s), [&](int s, int t){ return K(Q[s]) < K(Q[t]); });

	for (int qi : s) {
		pii q = Q[qi];
		while (L > q.first)  v.add(--L, 0);
		while (R < q.second) v.add(R++, 1);
		while (L < q.first)  v.del(L++, 0);
		while (R > q.second) v.del(--R, 1);
		v.calc(qi);
	}
}

struct Spec {
	using S = ll;
	void add(int ind, int end) {}
	void del(int ind, int end) {}
	void calc(int idx) {}
};
