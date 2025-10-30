/**
 * Author: Ruan Petrus
 * Description: Spec for seg tree implementation
 * Time: O(\log N)
 * Status: stress-tested
 */

struct Spec {
	using S = int;
	using K = int;
	static S op(S a, S b) { return max(a, b); }
	static S update(K f, S a) { return f + a; }
	static K compose(const K f, const K g) { return f + g; }
	static S id() { return 0; }
};
