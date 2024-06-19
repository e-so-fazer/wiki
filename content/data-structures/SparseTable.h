/**
 * Author: Arthur Botelho
 * Description: Multidimensional Sparse Table
 * Requires Idempotent Monoid S (op, inv, id)
 * Time: O(1) query, O((n \log n)^D) build
 * Memory: O((n \log n)^D)
 * Status: not yet tested
 */
#pragma once

#define MAs template<class...As> //multiple arguments
template<int D, class S>
struct SpTable{ using T = typename S::T;
	using isp = SpTable<D-1, S>;
	inline int lg(signed x){return __builtin_clz(1)-__builtin_clz(x);}
	int n;
	vector<vector<isp>> tab;
	MAs SpTable(int s, As... ds):n(s),
	tab(1+lg(n),vector<isp>(n,isp(ds...))){}
	MAs void set(T x, int p, As... ps){tab[0][p].set(x, ps...);}
	void join(SpTable& a, SpTable& b){
		rep(i, 0, 1+lg(n))rep(j, 0, n)
			tab[i][j].join(a.tab[i][j], b.tab[i][j]);
	}
	void init(){
		rep(i, 0, n)tab[0][i].init();
		rep(i, 0, lg(n))rep(j, 0, n-(1<<i))
			tab[i+1][j].join(tab[i][j], tab[i][j+(1<<i)]);
	}
	MAs T query(int l, int r, As... ps){
		int k = lg(r-l+1); r+=1-(1<<k);
		return S::op(tab[k][l].query(ps...),tab[k][r].query(ps...));
	}
};

template<class S>
struct SpTable<0, S>{ using T = typename S::T;
	T val=S::id;
	void set(T x){val=x;}
	void join(SpTable& a, SpTable& b){val=S::op(a.val,b.val);}
	void init(){}
	T query(){return val;}
};

struct IM{
	using T = int;
	static constexpr T id = 0;
	static T op(T a, T b){return max(a, b);}
};
