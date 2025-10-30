/**
 * Author: Ruan Petrus
 * Description: Iterative SegTree
 * Can be changed by modifying Spec
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once
#include "SegSpec.h"

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
