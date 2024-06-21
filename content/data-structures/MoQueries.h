/**
 * Author: Ruan Petrus
 * Description: Solve queries offline
 * Can be changed by modifying Spec
 * Time: $O(n * \sqrt(q))$
 * Status: not stress_tested
 */

vi mo(vector<pii> Q, vector<int> V) { // Queries in Q are [l, r)
	int L = 0, R = 0, blk = 350; // ∼N/sqrt (Q)

	vi s(sz(Q)), res = s;
	auto K = [&](pii x) {return pii(x.first/blk, x.second ^ -(x.first/blk & 1)); };
	iota(all(s), 0);
	sort(all(s), [&](int s, int t){ return K(Q[s]) < K(Q[t]); });

	int sum = 0;
	auto add =  [&](int ind, int end) { sum += V[ind]; }; // add a [ ind ] (end = 0 or 1)
	auto del =  [&](int ind, int end) { sum -= V[ind]; }; // remove a [ ind ]
	auto calc = [&]() { return sum; };                    // compute current answer

	for (int qi : s) {
		pii q = Q[qi];
		while (L > q.first) add(--L, 0);
		while (R < q.second) add(R++, 1);
		while (L < q.first) del(L++, 0);
		while (R > q.second) del(--R, 1);
		res[qi] = calc();
	}
	return res;
}
