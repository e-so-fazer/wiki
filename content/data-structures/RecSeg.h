/**
 * Author: Ruan Petrus
 * Description: Recursive generic persistent dinamic SegTree
 * Can be changed by modifying Spec, queries are inclusive exclusive
 * Time: O(\log N)
 * Memory: O(Q * \log N)
 * Status: Not stress tested
 */
#pragma once

template<typename LS>
struct Node {
	using S = typename LS::S;
	using K = typename LS::K;

	Node<LS> *l = 0, *r = 0;
	int lo, hi;
	S val = 0;

	Node() {}
	Node(int lo,int hi): lo(lo), hi(hi), val(LS::id()) {}

	S query(int L, int R) { // [L, R)
		if (R <= lo || hi <= L) return LS::id();
		if (L <= lo && hi <= R) return val;
		push();
		return LS::op(l->query(L, R), r->query(L, R));
	}
	Node<LS>* update(int idx, K x) {
		if (hi <= idx || idx < lo) return this;
		Node<LS>* me = new Node(lo, hi);
		push(); me->l = l; me->r = r;
		if (hi - lo == 1) me->val = LS::update(x, val);
		else {
			me->l = l->update(idx, x), me->r = r->update(idx, x);
			me->val = LS::op(me->l->val, me->r->val);
		}
		return me;
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
	}
};
