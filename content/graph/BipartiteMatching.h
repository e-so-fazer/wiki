/**
 * Author: Ruan Petrus
 * Description: Founds bipartite matching
 * Time: O(M * sqrt(N))
 * Memory: O(N + M)
 * Status: not stress-tested
*/

struct Kuhn {
    int n, m;
    vector<int> atob, btoa, nxt, dist, Q;
    vector<vector<int>> g;
	int qh = 0, qt = 0;

    Kuhn(int _n, int _m): n(_n), m(_m), 
		atob(n, -1), btoa(m, -1), nxt(n), dist(n), Q(n),
		g(n) 
	{}
	void add_edge(int a, int b) {
        g[a].pb(b);
    }

    bool bfs() {
        fill(all(dist), n); 
		qh = 0, qt = 0;

        for (int a = 0; a < n; a++) {
            if (atob[a] == -1) {
				dist[a] = 0;
				Q[qt++] = a;
			}
        }

        bool found = false;
        while(qh < qt) {
            int a = Q[qh++];
            for (int b: g[a]) {
                int c = btoa[b];
				if (c != -1) {
					if (dist[a] + 1 < dist[c]) {
						dist[c] = dist[a] + 1;
						Q[qt++] = c;
					}
				}
				else found = true;
            }
        }
        return found;
    }

    bool dfs(int a) {
        while(nxt[a] < (int)g[a].size()) {
            int b = g[a][nxt[a]++];
            int c = btoa[b];
            if (c == -1 || (dist[a] + 1 == dist[c] && dfs(c))) {
				btoa[b] = a;
                atob[a] = b;

                return true;
            }
        }
        return false;
    }

    vector<pair<int, int>> get_match() {
        while(bfs()) {
            fill(all(nxt), 0);
            for (int a = 0; a < n; a++) {
                if (atob[a] == -1) dfs(a);
            }
        }
        vector<pair<int, int>> ans;
        for (int b = 0; b < m; b++) {
            if (btoa[b] != -1) ans.eb(btoa[b], b);
        }
        return ans;
    }
};

// // Found for each vertex of left if he is necessary to maximal matching
// vector<bool> find_necessary_vertex(Kuhn & flow) {
// 	int n = flow.n;
// 	vector<bool> ans(n);
// 	assert(flow.bfs() == false);
// 	rep(i, 0, n) ans[i] = (flow.dist[i] == n);
// 	return ans;
// }
