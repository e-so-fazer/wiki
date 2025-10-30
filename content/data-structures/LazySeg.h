/**
 * Author: Ruan Petrus
 * Description: Iterative Lazy SegTree
 * Can be changed by modifying Spec
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once
#include "SegSpec.h"

template<typename Spec>
struct LazySeg {
	using LS = Spec;
	using S = typename LS::S;
	using K = typename LS::K;
	int n;
	vector<S> seg;
	vector<K> lazy;
	vector<bool> has_lazy;
	// vector<int> lx, rx; // Aditional info
	
    LazySeg(vector<S> & v) : n(sz(v)), seg(2*n) , lazy(n), has_lazy(n) {
		rep(no, 0, n) seg[no+n] = v[no];
		for (int no = n-1; no >= 1; no--) pull(no);

		// Aditional info, n must be power of two
		/*
		lx.assign(2*n, 0); rx.assign(2*n, 0);
		lx[1] = 0; rx[1] = n;
		rep(no, 1, n) {
			int mid = (lx[no] + rx[no])/2;
			lx[no*2]   = lx[no]; rx[no*2] = mid;
			lx[no*2+1] = mid;    rx[no*2+1] = rx[no];
		}
		*/
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
