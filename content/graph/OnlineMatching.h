/**
 * Author: Ruan Petrus
 * Description: Modified khun developed for specific question
 * able to run $2*10^6$ queries, in $2*10^6$ x $10^6$ graph in 3 seconds codeforces
 * Time: O(confia)
 * Status: not stress-tested
 */

struct OnlineMatching {
    int n = 0, m = 0;
    vector<int> vis, match, dist;
    vector<vector<int>> g;
	vector<int> last;
	int t = 0;

    OnlineMatching(int n_, int m_) : n(n_), m(m_),
		vis(n, 0), match(m, -1), dist(n, n+1), g(n), last(n, -1)
		{}

    void add(int a, int b) {
        g[a].pb(b);
    }

    bool kuhn(int a) {
		vis[a] = t;
		for(int b: g[a]) {
		    int c = match[b];
		    if (c == -1) {
				match[b] = a;
				return true;
		    }
		    if (last[c] != t || (dist[a] + 1 < dist[c])) 
				dist[c] = dist[a] + 1, last[c] = t;
		}
		for (int b: g[a]) {
			int c = match[b];
			if (dist[a] + 1 == dist[c] && vis[c] != t && kuhn(c)) {
				match[b] = a;
				return true;
			}
		}
        return false;
    }
	bool can_match(int a) {
		t++;
		last[a] = t;
		dist[a] = 0;
		return kuhn(a);
	}
};
