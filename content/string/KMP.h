/**
 * Author: Arthur Botelho
 * Description: KMP automaton
 * Time: O(n) build, O(1) query
 * Memory: O(26n)
 * Status: not yet tested
*/


struct KMP{
	const int inic = 'a';
	int n; vi pi; vector<vi> aut;
	KMP(string s):n(s.size()),pi(n),aut(n+1, vi(26,0)){
		rep(i, 1, n){
			int j = pi[i-1];
			while(j > 0 and s[j]!=s[i])j = pi[i-1];
			pi[i] = j + (s[i]==s[j]);
		}
		s.pb('#');
		rep(i, 0, n+1){
			rep(c, 0, 26){
				if (i > 0 and c+inic!=s[i])aut[i][c] = aut[pi[i-1]][c];
				else aut[i][c] = i + (c+inic == s[i]);
			}
		}
	}
	pair<bool, int> nxt(int cur, char c){
		cur = aut[cur][c];
		return {cur==n, cur};
	}
};
	
