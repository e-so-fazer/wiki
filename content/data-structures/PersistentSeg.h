/**
 * Author: Arthur Botelho
 * Description: Persistent Segment Tree
 * Requires Monoid (op, id)
 * Time: O(\log N)
 * Memory: O(|updates| \log N)
 * Status: not tested
 */

/* 

	Observations:
		- Call one of the "init"s to get an initial root!
		- Node 0 is a "blank" node, the default child of any node
		- MXN should be Memory / (2 * int + T)
	Complexity:
		- Query: O(log(n) * op)
		- Update: O(log(n) * op)
		- Build: O(1) or O(n * op)
		- Memory: O(((1 or 2 * n) + qnt_updt * log(n)) * (2 * int + T))
*/

#define midpoint(l, r) (l + (r-l)/2)
template<class I, class S> //index type and algebraic structure
struct PersistentSeg{
	using P = int; //pointer type
	using T = typename S::T; //value type
	struct Node{P lc, rc; T val;};
	I n; vector<Node> v;
	P new_node(T val=S::id){return v.eb(0,0,val), sz(v)-1;}
	P new_node(P l, P r){return v.eb(l,r,S::op(v[l].val, v[r].val)), sz(v)-1;}
	PersistentSeg(){ //only creates object, should be "init"ed to get root
		//v.reserve(MXN); //faster node creation
		new_node(); //blank node
	}
	P init(I s){return n = s, new_node();}
	P init(vector<T> a){
		auto build = [&](auto rec, I lx, I rx)->P{
			if (lx==rx)return new_node(a[lx]);
			I mx = midpoint(lx, rx);
			return new_node(rec(rec, lx, mx), rec(rec, mx+1, rx));
		}; return build(build, 0, (n = sz(a))-1);
	}
	P update(T x, I p, P root){return update(x, p, root, 0, n-1);}
	P update(T x, I p, P i, I lx, I rx){
		if (lx==rx){return new_node(x);}
		I mx = midpoint(lx, rx);
		if (p > mx)return new_node(v[i].lc, update(x, p, v[i].rc, mx+1, rx));
		else return new_node(update(x, p, v[i].lc, lx, mx), v[i].rc);
	}
	T query(I l, I r, P root){return query(l, r, root, 0, n-1);}
	T query(I l, I r, P i, I lx, I rx){
		if (l <= lx and rx <= r)return v[i].val;
		if (lx > r or rx < l)return S::id;
		I mx = midpoint(lx, rx);
		return S::op(query(l, r, v[i].lc, lx, mx), query(l, r, v[i].rc, mx+1, rx));
	}
};


struct Sum{
	using T = long;
	static constexpr T id = 0;
	static T op(T a, T b){return a + b;}
};