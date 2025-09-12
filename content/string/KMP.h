/**
 * Author: Arthur Botelho
 * Description: KMP automaton
 * Time: O(N) build, O(1) query (amortized)
 * Memory: O(N)
 * Status: stress tested
*/

template<class S> struct KMP {
	S p; int n; vector<int> nb;
	KMP(S& ap) : p(ap), n(sz(p)), nb(n+1) {
		for(int k = 1; k < n; k++) nb[k+1] = nxt(nb[k], P[k]);
	}
	
	int nxt(int i, auto c){
		for(; i; i = nb[i])if (i < n and P[i]==c)return i+1;
		return P[0]==c;
	}
};

/* DFA
	vector<vector<int>> dfa(n+1, vector<int>(26));
    void build_dfa(){
        dfa[0][P[0]] = 1; //only way to advance at 0
        for(int k = 1; k <= n; k++)
            for(int c = 0; c < 26; c++)
                if (k < n and P[k] == 'a'+c) dfa[k][c] = k+1;
                else dfa[k][c] = dfa[neighbor[k]][c];
    }
*/