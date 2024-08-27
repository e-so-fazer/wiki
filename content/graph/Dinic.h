/**
 * Author: Arthur Botelho
 * Description: finds maximum network flow
 * Time: O(V*E*log(maxVal))
 * Memory: O(V+E)
 * Status: not yet tested
  */
/*
  Observations:
  * --- Edge capacity is implemented as "remaining capacity for flow",
  *		without variable for current passing flow
  *	--- Zero limit (eps) should be changed according to required precision
  *		for float capacity edges
  *		Tested at: CSES-Download Speed 
*/
template<class T>
struct Dinic{
	struct Edge{int a, b; T w; bool rev;};
	int n, m; T mx;
	vector<vi> g; vector<Edge> es;
	Dinic(int s):n(s),m(0),mx(1),g(n){}
	
	void add_edge(int a, int b, T w){
		g[a].pb(m++); g[b].pb(m++);
		es.pb({a,b,w,false}); es.pb({b,a,T(0),true});
		while(w>=mx)mx+=mx;
	}
	
	T maxflow(int source, int sink){
		T eps = T(1)/T(oo); //associated to constant for float flow
		vi ce(n, 0), dep(n, -1);
		auto make_dag = [&](T cmx)->bool{
			ce.assign(n, 0); dep.assign(n, -1);
			queue<int> q; q.push(source); dep[source] = 0;
			while(not q.empty()){
				int v = q.front(); q.pop();
				for(int i : g[v]){ auto& e = es[i];
					if (e.w < cmx or dep[e.b]!=-1)continue;
					dep[e.b] = dep[v]+1; q.push(e.b);
				}
			}
			return dep[sink]!=-1;
		};
		auto push_flow = [&](auto rec, int v, T f)->T{
			if (v==sink)return f;
			T cur(0);
			for(int& i = ce[v]; i < sz(g[v]); i++){
				int j = g[v][i]; auto& e = es[j];
				if (dep[e.b]!=dep[e.a]+1 or e.w<=eps)continue;
				T cf = rec(rec, e.b, min(e.w, f));
				f -= cf; cur += cf; e.w -= cf; es[j^1].w += cf;
				if (f<=eps)return cur;
			}
			return cur;
		};
		T res(0);
		for(T cmx=mx,cf; cmx>eps;cmx/=T(2)){ while(make_dag(cmx))
			while((cf=push_flow(push_flow,source,T(oo)))>eps)res += cf;
		}
		return res;
	}
};
