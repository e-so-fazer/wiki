/**
 * Author: Ruan Petrus
 * Description: Persistent Sparse Lazy Seg
 * Can be changed by modifying Spec
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once
#include "SegSpec.h"

template<typename LS>
struct PersistentSeg {
	using S = typename LS::S;
	using K = typename LS::K;

	static constexpr int mxN = 5e7;
	// Hoping keeping types together will reduce memory cost alignment
	int l[mxN], r[mxN];
	S val[mxN];
	bool has_lazy[mxN];
	K lazy[mxN];

	int segID = 0;

	PersistentSeg() : segID(0) {
		alloc(); // Using 0 as the id node
	}
	S query(int L, int R, int no, int lo, int hi) { // [L, R)
		if (R <= lo || hi <= L)      return LS::id();
		else if (L <= lo && hi <= R) return val[no];
		else {
			push(no, lo, hi);
			int mid = lo + (hi-lo)/2;
			return LS::op(
				query(L, R, l[no], lo, mid), 
				query(L, R, r[no], mid, hi)
			);
		}
	}
	int alloc() {
		int no = segID++;
		// If not enough memory try to wrap around and hope it will work
		if (segID >= mxN) segID = 1; 

		l[no] = -1; r[no] = -1;
		val[no] = LS::id();
		has_lazy[no] = false;
		return no;
	}
	int update(int L, int R, K x, int no, int lo, int hi) { // [L, R)
		if (R <= lo || hi <= L)      return no;
		else if (L <= lo && hi <= R) return apply(x, no, lo, hi);
		else {
			push(no, lo, hi);
			int me = alloc();
			int mid = lo + (hi-lo)/2;
			l[me] = update(L, R, x, l[no], lo, mid); 
			r[me] = update(L, R, x, r[no], mid, hi);
			val[me] = LS::op(val[l[me]], val[r[me]]);
			return me;
		}
	}
	void push(int no, int lo, int hi) {
		if (hi - lo > 1) {
			if (l[no] == -1) {
				l[no] = r[no] = 0; // Using the 0 as the ID node
			}
			if (has_lazy[no]) {
				int mid = lo + (hi-lo)/2;
				l[no] = apply(lazy[no], l[no], lo, mid); 
				r[no] = apply(lazy[no], r[no], mid, hi);
				has_lazy[no] = false;
			}
		}
	}
	int apply(K v, int no, int lo, int hi) {
		int me = alloc();
		l[me] = l[no]; r[me] = r[no];
		val[me] = LS::update(v, val[no], lo, hi);
		if (hi - lo > 1) {
			if (has_lazy[no]) lazy[me] = LS::compose(v, lazy[no]);
			else lazy[me] = v;
			has_lazy[me] = true;
		}
		return me;
	}
};
