/**
 * Author: Eduardo Freire
 * Description: Treap
 * Time: O(log(b))
 * Memory: O(n)
 * Status: not yet tested
 */

struct Treap {
	typedef Treap T;
	T *l, *r;	
	int s, w;

	Treap(int aval) : s(1), w(rand()) {
		l=r=0;
	}

	~Treap() {
		if (l != 0) delete l;
		if (r != 0) delete r;
	}
	static int size(T *no) {
		if (no == 0) return 0;
		return no->s;
	}

	static pair<T*, T*>split(T *no, int k) {
		if (no == 0) return {0,0};
		return no->split(k);
	}

	pair<T*, T*> split(int k) {
		T *nl, *nr, *sl, *sr;
		if (size(l) < k) {
			if (r == 0) sl=sr=0;
			else tie(sl,sr) = r->split(k-size(l)-1);
			r=sl; nr=sr; nl=this;
		} else {
			if (l == 0) sl=sr=0;
			else tie(sl,sr) = l->split(k);
			nl=sl; l=sr; nr=this;
		}

		s = size(l)+size(r)+1;
		return {nl,nr};
	}

	static T* merge(T *l, T *r) {
		if (l == 0) return r;
		if (r == 0) return l;

		T *ans;
		if (l->w < r->w) ans=l, ans->r=merge(l->r,r);
		else ans=r, ans->l=merge(l,r->l);

		ans->s = size(ans->l) + size(ans->r) + 1;
		return ans;
	}
};
