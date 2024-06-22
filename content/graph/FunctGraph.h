/**
 * Author: Arthur Botelho
 * Description: Functional Graph
 * Time: O(n)
 * Memory: O(n)
 * Status: not yet tested
*/

struct FunctGraph{
	int n;
	vector<vi> gr, comps;
	vi head;
	
	FunctGraph(vi& fn):
		n(sz(fn)), head(n, -1), gr(n){
		rep(i, 0, n)gr[fn[i]].pb(i);
		vi visited(n, 0);
<<<<<<< HEAD
		auto dfs = [&](auto rec, int v, int c)->void{
=======
		auto dfs = [&](auto rec, int v, int c) -> void{
>>>>>>> d4974a2bbda5c1a11210e7c7ea447b895acf1691
			head[v] = c; visited[v] = 1;
			for(int f : gr[v])if (head[f]!=f)rec(rec, f, c);
		};
		rep(i, 0, n){
			if (visited[i])continue;
			int l=fn[i], r=fn[fn[i]];
			while(l!=r) l=fn[l],r=fn[fn[r]];
			vi cur = {r}; l = fn[l];
			for(;l!=r;l=fn[l]) cur.pb(l);
			for(int x : cur) head[x] = x;
			for(int x : cur) dfs(dfs, x, x);
			comps.pb(cur);
		}
	}
};
