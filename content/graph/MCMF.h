/**
 * Author: Arthur Botelho
 * Description: minimum cost for maximum flow in network
 * Time:
 *	--- Preprocessing: SPFA (O(V*E))
 *	--- Max number of iterations: min(maxflow, max cost path)
 *	--- Complexity for each iteration:
 *	--- Dijkstra: O(V+ElogE)
 *	--- DFS: O(E*V)?
 * Memory: O(V+E)
 * Status: not yet tested
 * Observations:
 * --- pots_init is only useful if there are negative initial costs
 * --- Dijkstra path recover can be used as (slower?) alternative to push flow
 */

template<class TF, class TC>
struct MCMF{
	struct Edge{int a, b; TF w; TC c;};
	int n, m;
	vector<vi> g; vector<Edge> es;
	MCMF(int s):n(s),m(0),g(n){}
	
	void add_edge(int a, int b, TF w, TC c){
		g[a].pb(m++); g[b].pb(m++);
		es.pb({a, b, w, c}); es.pb({b, a, TF(0), -c});
	}
	
	pair<TF, TC> mcmf(int source, int sink){
		TF eps = TF(1)/TF(oo);
		vector<TC> ds(n,TC(0)), ps(n,TC(0));
		vi ce(n, 0), on(n, 0);
		auto ecost = [&](Edge& e)->TC{return ps[e.a]-ps[e.b]+e.c;};
		auto pots_init = [&]()->void{
			ps.assign(n, TC(oo)); vi inq(n, 0); 
			queue<int> q; q.push(source);
			inq[source] = 1; ps[source] = 0;
			while(not q.empty()){
				int v = q.front(); q.pop(); inq[v] = 0;
				for(int i : g[v]){ auto& e = es[i];
					if (e.w<=eps or ps[e.b]<=ps[v]+e.c)continue;
					if (not inq[e.b])q.push(e.b);
					inq[e.b] = 1; ps[e.b] = ps[v]+e.c;
				}
			}
		};
		auto dists_calc = [&]()->bool{
			rep(v, 0, n)if (ps[v]<TC(oo))ps[v]+=ds[v];
			ds.assign(n, TC(oo)); ce.assign(n, 0);
			vi vis(n, 0); using P = pair<int, TC>;
			priority_queue<P, vector<P>, greater<P>> pq;
			pq.push({ds[source]=TC(0), source});
			while(not pq.empty()){
				auto [d, v] = pq.top(); pq.pop();
				if (vis[v])continue;
				vis[v] = true;
				for(int i : g[v]){ auto& e = es[i];
					if (e.w<=eps or ds[e.b]<=d+ecost(e))continue;
					pq.push({ds[e.b]=d+ecost(e), e.b});
				}
			}
			return ds[sink]!=TC(oo);
		};	
		auto push_flow = [&](auto rec, int v, TF f)->pair<TF, TC>{
			if (v==sink)return {f, TC(0)};
			on[v] = 1; TF curf(0); TC curc(0);
			for(int& i = ce[v]; i < sz(g[v]); i++){
				int j = g[v][i]; auto& e = es[j];
				if (on[e.b] or e.w<=eps)continue;
				if (ecost(e)>ds[e.b]-ds[e.a])continue;
				auto [cf, cc] = rec(rec, e.b, min(f, e.w));
				f-=cf; curf+=cf; e.w-=cf; es[j^1].w+=cf;
				curc += e.c*cf + cc;
				if (f<=eps){on[v] = 0; return {curf, curc};}
			}
			on[v] = 0; return {curf, curc};
		};
		TF flow(0), cf(oo); TC cost(0), cc(0); 
		for(pots_init();dists_calc();)
			for(cf=TF(oo);cf>eps;flow+=cf,cost+=cc)
				tie(cf, cc)=push_flow(push_flow,source,TF(oo));
		return {flow, cost};
	}
};
