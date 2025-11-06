/**
 * Author: Arthur Botelho
 * Description: Persistent Lazy Sparse Segment Tree
 * Can be changed by modifying Spec
 * Time: O(\log N)
 * Status: not stress-tested
 */

 #define midpoint(l, r) (l+(r-l)/2)
template<class I, class S> //index type and algebraic structure
struct LazyPersistentSeg{ 
	using P = int; //pointer type
	using T = typename S::T; //value type
	using L = typename S::L; //lazy type
	struct Node{P lc, rc; T val; L lz; bool ig;};
	I n; vector<Node> v;
	P new_node(T val = S::id){return v.eb(0,0,val,L(),1), sz(v)-1;}
	P new_node(P l, P r){return v.eb(l,r,S::op(v[l].val,v[r].val),L(),1), sz(v)-1;}
	P lazy_clone(P i, L lz, I lx, I rx){
		P ni = new_node(v[i].lc, v[i].rc);
		v[ni].lz = v[i].ig ? lz : S::cmp(v[i].lz, lz); 
		v[ni].ig = 0;
		v[ni].val = S::ch(v[i].val, lz, lx, rx);
		return ni;
	}
	LazyPersistentSeg(){ //only creates object, should be "init"ed to get root
		//v.reserve(MXN); //faster node creation
		new_node(); //blank node
	}
	P init(I s){return n = s, new_node();}
	P init(vector<T> a){
		auto build = [&](auto rec, I lx, I rx)->P {
			if (lx==rx)return new_node(a[lx]);
			I mx = midpoint(lx, rx);
			return new_node(rec(rec, lx, mx), rec(rec, mx+1, rx));
		}; return build(build, 0, (n = sz(a))-1);
	}
	void prop(P i, I lx, I rx){
		if (v[i].ig)return;
		int mx = midpoint(lx, rx);
		if (lx < rx){
			v[i].lc = lazy_clone(v[i].lc, v[i].lz, lx, mx);
			v[i].rc = lazy_clone(v[i].rc, v[i].lz, mx+1, rx);
		}
		v[i].ig = 1;
	}
	P update(L lz, I l, I r, P root){return update(lz, l, r, root, 0, n-1);}
	P update(L lz, I l, I r, P i, I lx, I rx){
		if (lx > r or rx < l)return i;
		if (l <= lx and rx <= r)return lazy_clone(i, lz, lx, rx);
		prop(i, lx, rx);
		I mx = midpoint(lx, rx);
		return new_node(update(lz, l, r, v[i].lc, lx, mx), update(lz, l, r, v[i].rc, mx+1, rx));
	}
	T query(I l, I r, P root){return query(l, r, root, 0, n-1);}
	T query(I l, I r, P i, I lx, I rx){
		if (lx > r or rx < l)return S::id;
		if (l <= lx and rx <= r)return v[i].val;
		prop(i, lx, rx);
		I mx = midpoint(lx, rx);
		return S::op(query(l, r, v[i].lc, lx, mx), query(l, r, v[i].rc, mx+1, rx));
	}
};
