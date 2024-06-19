/**
 * Author: Arthur Botelho
 * Description: Multidimensional SegTree
 * Requires Monoid S (op, id)
 * Time: O((\log N)^D)
 * Memory: O(N^D)
 * Status: not yet tested
 */
//#pragma once

#define MAs template<class... As> //multiple arguments
template<int D, class S>
struct SegTree{ using T = typename S::T;
	int n;
	vector<SegTree<D-1, S>> seg;
	MAs SegTree(int s, As... ds):n(s),seg(2*n, SegTree<D-1, S>(ds...)){}
	MAs T get(int p, As... ps){return seg[p+n].get(ps...);}
	MAs void update(T x, int p, As... ps){
		p+=n; seg[p].update(x, ps...);
		for(p>>=1;p>=1;p>>=1)
		seg[p].update(S::op(seg[2*p].get(ps...),seg[2*p+1].get(ps...)), ps...);
	}
	MAs T query(int l, int r, As... ps){
		T lv=S::id,rv=S::id;
		for(l+=n,r+=n+1;l<r;l>>=1,r>>=1){
			if (l&1)lv = S::op(lv,seg[l++].query(ps...));
			if (r&1)rv = S::op(seg[--r].query(ps...),rv);
		}
		return S::op(lv,rv);
	}
};
 
template<class S>
struct SegTree<0, S>{ using T = typename S::T;
	T val=S::id;
	T get(){return val;}
	void update(T x){val=x;}
	T query(){return val;}
};

struct M{ //monoid
	using T = int;
	static constexpr T id = 0;
	static T op(T a, T b){return max(a,b);}
};