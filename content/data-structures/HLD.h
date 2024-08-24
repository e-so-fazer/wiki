/**
 * Author: Eduardo Freire
 * Description: Iterative, lazy, noncommutative HLD
 * Can be changed by modifying Spec, exactly like a segment tree
 * Time: query: O(\log^2 N), point update: O(\log N), range update: O(\log^2 N)
 * Status: stress-tested
 */

template<class T>
struct HLD {
	using S = typename T::S;
	using K = typename T::K;
	vvi g;
	int rt,n,dt;
	vi hv, ti,to, hd, p, ssz;
	SegTree<T> seg;
	HLD(vvi ag, int art=0) :
		g(ag),rt(art),n(g.size()),dt(0),
		hv(n),ti(n),to(n),hd(n),p(n), ssz(n),seg(n)
	{
		dfs1(rt,rt);
		dfs2(rt,rt);
	}

	void dfs1(int a, int pai) {
		p[a]=pai;
		ssz[a]=1;

		pii hc(-1,-1);
		for (auto b:g[a]) if(b!=pai) {
			dfs1(b,a);
			hc=max(hc, pii(ssz[b], b));
			ssz[a]+=ssz[b];
		}
		hv[a]=hc.second;
	}

	void dfs2(int a, int h) {
		hd[a]=h;
		ti[a]=dt++;
		if (hv[a] != -1) dfs2(hv[a], h);
		for (auto b:g[a]) if (b != p[a] and b != hv[a])
			dfs2(b, b);
		to[a]=dt;
	}

	bool isa(int a, int b) {
		return ti[a]<=ti[b] and to[a]>=to[b];
	}

	// if T::op is commutative then queryI can be replaced by query.	
	// To implement seg.queryI, keep a second vector on the SegTree struct which will
	// represent the segtree with operations swapped. Copy paste the query method
	// and change every occorrence of T::op(a,b) with T::op(b,a). Similarly for the update.
	// seg.query(l, r) must query [l, r).
	// Query path from a to b, inclusive on both ends.
	S query(int a, int b) {
		// SegTree identity		
		S a1=T::id(),a2=T::id();

		for (;!isa(hd[a], b); a=p[hd[a]])
			a1=T::op(a1, seg.queryI(ti[hd[a]], ti[a]+1));

		for(;!isa(hd[b],a);b=p[hd[b]])
			a2=T::op(seg.query(ti[hd[b]], ti[b]+1), a2);

		if (isa(a,b)) a2=T::op(seg.query(ti[a], ti[b]+1), a2);
		else a1=T::op(a1, seg.queryI(ti[b], ti[a]+1));
		return T::op(a1, a2);
	}

	// Remember that if T::op is not commutative, "update" must update the inverse seg as well.
	void update(int a, K v) {
		seg.update(ti[a], v);
	}
	
	// lazy update on path from a to b, inclusive on both ends.
	void update(int a, int b, K v) {
		for (;!isa(hd[a], b); a=p[hd[a]])
			seg.update(ti[hd[a]], ti[a]+1, v);

		for(;!isa(hd[b],a);b=p[hd[b]])
			seg.update(ti[hd[b]], ti[b]+1, v);

		if (isa(a,b)) seg.update(ti[a], ti[b]+1, v);
		else seg.update(ti[b], ti[a]+1, v);
	}
};

