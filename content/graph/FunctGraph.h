/**
 * Author: Arthur Botelho
 * Description: Functional Graph
 * Time: O(n)
 * Memory: O(n)
 * Status: not yet tested
*/

struct FunctGraph{
	int n;
	vi head, comp;
	vector<vi> gr, cycles;
	
	FunctGraph(vi& fn):
		n(sz(fn)), head(n, -1), comp(n), gr(n) {
		rep(i, 0, n)gr[fn[i]].pb(i);
		vi visited(n, 0);
		auto dfs = [&](auto rec, int v, int c) -> void{
			head[v] = c; visited[v] = 1;
			for(int f : gr[v])if (head[f]!=f)rec(rec, f, c);
		};
		rep(i, 0, n){
			if (visited[i])continue;
			int l=fn[i], r=fn[fn[i]];
			while(l!=r) l=fn[l], r=fn[fn[r]];
			vi cur = {r}; 
			for(l=fn[l]; l!=r; l=fn[l]) cur.pb(l);
			for(int x : cur) head[x] = x, comp[x] = sz(cycles);
			cycles.pb(cur);
			for(int x : cur) dfs(dfs, x, x);
		}
	}
};
