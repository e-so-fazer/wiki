/**
 * Author: Arthur Botelho
 * Description: Shortest distances from source vertex
 * Time: O(V*E), SPFA may be O(E) in random graphs
 * Memory: O(V+E)
 * Status: not stress-tested
*/

template<class T>
vector<T> bellmanford(vi sources, vector<vector<pair<int, T>>> & g){
	int n = sz(g); vector<T> dists(n, T(oo));
	for(int s : sources)dists[s] = T(0);
	bool worked = true;
	vector<tuple<T, int, int>> edges;
	rep(a, 0, n)for(auto [b, c] : g[a])edges.pb({c, a, b});
	rep(i, 0, n+1){
		for(auto [c, a, b] : edges){
			if (dists[a]==T(oo))continue;
			if (dists[a]+c < dists[b]){
				if (i<n)dists[b] = dists[a]+c;
				else worked = false;
			}
		}
	}
	if (not worked)dists.clear(); //negative cycle returns empty vector
	return dists;
}

template<class T>
vector<T> spfa(vi sources, vector<vector<pair<int, T>>> & g){
	int n = sz(g); vector<T> dists(n, T(oo));
	vector<bool> inq(n, false); vi visited(n, 0);
	queue<int> q;
	for(int s : sources){
		q.push(s); inq[s] = true; dists[s] = T(0);
	}
	while(not q.empty()){
		int v = q.front(); q.pop(); inq[v] = false;
		if (visited[v]>n)return vector<T>();
		for(auto [adj, d] : g[v]){
			if (dists[adj]>dists[v]+d){
				dists[adj] = dists[v]+d;
				if (not inq[adj])q.push(adj); 
				inq[adj] = true; visited[adj]++;
			}
		}
	}
	return dists;
}