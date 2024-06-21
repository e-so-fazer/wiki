/**
 * Author: Ruan Petrus
 * Description: Suffix automata
 * Time: O(n) build
 * Memory: O(n * 26)
 * Status: not yet tested
 */

struct Automata {
	int saID = 1, last = 1;
	int n;
	vector<int> len, lnk;
	vector<array<int,27>> to;
	vector<int> occ, fpos;
	vector<int> states;

	Automata(const string & s, const char a = 'a') 
		: n(s.size()), len(2*n+2), lnk(2*n+2), to(2*n+2, {0}), occ(2*n+2), fpos(2*n+2) {
		for (const auto & c: s) push(c-a);

		states.assign(saID, 0);
		iota(all(states), 1);
		sort(all(states), [&](const auto & u, const auto & v) { return len[u] > len[v]; });
		for (auto st: states) {
			occ[lnk[st]] += occ[st];
		}
	}

	void push(int c) {
		int a = ++saID;
		int p = last;
		last = a;

		len[a] = len[p] + 1;
		occ[a] = 1;
		fpos[a] = len[a] - 1;

		for (; p > 0 && !to[p][c]; p = lnk[p]) to[p][c] = a;
		int q = to[p][c];
		if (p == 0) {
			lnk[a] = 1;
		}
		else if (len[p] + 1 == len[q]) {
			lnk[a] = q;
		}
		else {
			int clone = ++saID;
			lnk[clone] = lnk[q];
			to[clone] = to[q];
			fpos[clone] = fpos[q];

			len[clone] = len[p] + 1;
			lnk[a] = lnk[q] = clone;
			for (; to[p][c] == q; p = lnk[p]) to[p][c] = clone;
		}
	}
};
