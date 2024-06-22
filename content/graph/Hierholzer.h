/**
 * Author: Arthur Botelho
 * Description: Eulerian path/cycles if existing
 * Time: O(E)
 * Memory: O(V+E)
 * Status: not stress-tested
*/

vi hierholzer(int n, vector<pii>& edges, int inic){
	vi ans; int m = sz(edges);
	auto check = [&]()->bool{return true;};
	if (not check()){
		//a function should be created to check conditions
		//acording to type of graph and problem restrictions on
		//the path type and enpoints
		//base conditions: edge connectivity and vertex degree
		return ans; //empty vector if impossible
	}
	vector<vi> g(n);
	rep(i, 0, m){
		auto [a, b] = edges[i];
		g[a].pb(i); g[b].pb(i); //remove the latter if it's directed
	}
	vi used(m, false), st = {inic};
	while(not st.empty()){
		int v = st.back();
		while(not g[v].empty() and used[g[v].back()])g[v].pop_back();
		if (g[v].empty())st.pop_back(), ans.pb(v);
		else {
			int idx = g[v].back(); g[v].pop_back();
			auto [a, b] = edges[idx]; used[idx] = true;
			st.pb((v==a ? b : a));
		}
	}
	reverse(all(ans));
	return ans;
}