/**
 * Author: Arthur Botelho
 * Description: Multidimensional BIT/Fenwick Tree
 * Requires Abelian Group (op, inv, id)
 * Time: O((\log N)^D)
 * Memory: O(N^D)
 * Status: stress-tested
 */
#pragma once

#define MAs template<class... As> //multiple arguments
template<int D, class S>
struct BIT{ using T = typename S::T;
	int n;
	vector<BIT<D-1, S>> bit;
	MAs BIT(int s, As... ds):n(s),bit(n+1, BIT<D-1, S>(ds...)){}
	inline int lastbit(int x){return x&(-x);}
	MAs void add(T x, int p, As... ps){
		for(p++;p<=n;p+=lastbit(p))bit[p].add(x, ps...);
	}
	MAs T query(int l, int r, As... ps){
		T lv=S::id,rv=S::id; r++;
		for(;r>=1;r-=lastbit(r))rv=S::op(rv,bit[r].query(ps...));
		for(;l>=1;l-=lastbit(l))lv=S::op(lv,bit[l].query(ps...));
		return S::op(rv,S::inv(lv));
	}
};

template<class S>
struct BIT<0, S>{ using T = typename S::T;
	T val=S::id;
	void add(T x){val=S::op(val,x);}
	T query(){return val;}
};

struct AG{ //abelian group analogous to int addition
	using T = int;
	static constexpr T id = 0;
	static T op(T a, T b){return a+b;}
	static T inv(T a){return -a;}
};