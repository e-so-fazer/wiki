/**
 * Author: Eduardo Freire
 * Description: Aho automaton
 * Time: O(alphabet size * n) build, O(1) query
 * Memory: O(alphabet size * n)
 * Status: not yet tested
*/

struct Aho {
	int n=1, si; char in;
	vvi tran, nxt;
	vi lnk, term, h;
 
	// ain= initial alphabet letter, asi = alphabet size
	Aho(char ain, int asi) {
		in = ain;
		si = asi;
		tran.eb(si,-1);
		term.pb(0);
	}
 
	void add(string& s) {
		int cur=0;
		rep(i,0,s.size()) {
			int& nxt= tran[cur][s[i]-in];
			if (nxt != -1) cur=nxt;
			else nxt=cur=n++, term.pb(0),tran.eb(si,-1);
		}
		term[cur]+=1;
	}
 
	void init() {
		lnk.assign(n,0);
		nxt.assign(n, vi(si));
		h.assign(n,0);
 
		queue<int> q;
		rep(c,0,si) {
			int& f=tran[0][c];
			if (f != -1) q.push(f), h[f]=1, nxt[0][c]=f;
			else nxt[0][c]=0;
		}
		while (!q.empty()) {
			int a=q.front(); q.pop();
			rep(c,0,si) {
				int& b=nxt[a][c];
				int fail=nxt[lnk[a]][c];
				if (tran[a][c] != -1) {
					b = tran[a][c];
					lnk[b] = fail;
					q.push(b);
					h[b]=h[a]+1;
				} else b=fail;
			}
		}
	}
};

