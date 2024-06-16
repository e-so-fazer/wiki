/**
 * Author: Ruan Petrus
 * Description: Iterative SegTree
 * Can be changed by modifying Spec
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once

template<typename Spec>
struct SegTree {
	using LS = Spec;
	using S = typename LS::S;
	using K = typename LS::K;
	int n;
	vector<S> seg;

	SegTree(const vector<S> & v)
		: n(sz(v)), seg(2*n) {
		rep(i, 0, n) seg[i+n] = v[i];
		for(int i = n-1; i >= 1; i--) seg[i] = LS::op(seg[i*2], seg[i*2+1]);
	}

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
	using S = int;
	using K = int;
	static S op(S a, S b) { return max(a, b); }
	static S update(K f, S a) { return f + a; }
	static S id() { return 0; }
};
