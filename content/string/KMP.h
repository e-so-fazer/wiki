/**
 * Author: Arthur Botelho, Eduardo Freire
 * Description: KMP automaton
 * Time: O(alphabet size * n) build, O(1) query
 * Memory: O(alphabet size * n)
 * Status: not yet tested
*/

template<class T>
struct KMP{
	T in; int n; vi p; vector<vi> a;
	template<class S>
	KMP(S s, T ain, int asz):n(sz(s)),p(n), in(ain), a(n+1, vi(asz,0)){
		rep(i, 1, n){
			int j = p[i-1];
			while(j and s[j]!=s[i])j = p[j-1];
			p[i] = j + (s[i]==s[j]);
		}
		rep(i, 0, n+1)
			rep(c, 0, asz){
				if (i and (i==n or c+in!=s[i]))a[i][c] = a[p[i-1]][c];
				else a[i][c] = i + (c+in == s[i]);
			}
	}
	int nxt(int cur, T c){
		return a[cur][c-in];
	}
};

