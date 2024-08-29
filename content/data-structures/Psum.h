/**
 * Author: Arthur Botelho
 * Description: Multidimensional Psum
 * Requires Abelian Group (op, inv, id)
 * Time: O(1)
 * Memory: O(N^D)
 * Status: stress-tested
 */
#pragma once

#define MAs template<class... As> //multiple arguments
template<int D, class S>
struct Psum{ using T = typename S::T;
	int n;
	vector<Psum<D-1, S>> v;
	MAs Psum(int s, As... ds):n(s+1),v(n,Psum<D-1, S>(ds...)){}
	MAs void set(T x, int p, As... ps){v[p+1].set(x, ps...);}
	void push(Psum& p){rep(i, 1, n)v[i].push(p.v[i]);}
	void init(){rep(i, 1, n)v[i].init(),v[i].push(v[i-1]);}
	MAs T query(int l, int r, As... ps){
		return S::op(v[r+1].query(ps...),S::inv(v[l].query(ps...)));
	}
};

template<class S>
struct Psum<0, S>{ using T = typename S::T;
	T val=S::id;
	void set(T x){val=x;}
	void push(Psum& a){val=S::op(a.val,val);}
	void init(){}
	T query(){return val;}
};

struct G{
	using T = int;
	static constexpr T id = 0;
	static T op(T a, T b){return a+b;}
	static T inv(T a){return -a;}
};