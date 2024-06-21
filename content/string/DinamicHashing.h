/**
 * Author: Ruan Petrus
 * Description: Dinamic string hashing
 * Time: O(1) query, O(n) build
 * Memory: O(n)
 * Status: not yet tested, not working
 */

typedef uint64_t ull;

template<int M, class B>
struct A {
	int x; B b; 
	constexpr A(int x=0) : x(x), b(x) {}
	constexpr A(int x, B b) : x(x), b(b) {}
	A operator+(A o) const {int y = x+o.x; return{y - (y>=M)*M, b+o.b};}
	A operator-(A o) const {int y = x-o.x; return{y + (y< 0)*M, b-o.b};}
	A operator*(A o) const { return {(int)(1LL*x*o.x % M), b*o.b}; }
	explicit operator ull() const { return x ^ (ull) b << 21; }
	bool operator==(A o) const { return (ull)*this == (ull)o; }
	bool operator<(A o) const { return (ull)*this < (ull)o; }
};

typedef A<989831283,  A<912391239 , unsigned>> H;

const static int C = 12312;

struct DinamicHash {
	int n;
	vector<int> s;
	vector<H> p;
	SegTree seg;
	DinamicHash(const vector<int> & v) : n(v.size()), s(v), p(n+1) {
		p[0] = 1;
		vector<H> values(n);
		rep(i, 0, n) {
			values[i] = p[i] * s[i];
			p[i+1] = p[i] * C;
		}
		seg = SegTree(values);
	};
	H query(int l, int r) const { // [l, r)
		return seg.query(l, r) * p[n-r];
	}
	void update(int idx, int v) {
		s[idx] = v;
		seg.update(idx, p[idx] * s[idx]);
	}
};

