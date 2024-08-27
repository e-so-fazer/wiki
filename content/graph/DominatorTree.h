/**
 * Author: Ruan Petrus
 * Description: Dominator Tree, creates the graph \texttt{tree}, where all ancestors of a \texttt{u} in the tree 
 * are necessary in the path from the \texttt{root} to \texttt{u}
 * Time: O((n + m)log(n)) build
 * Memory: O(n)
 * Status: not yet tested
 */

struct DominatorTree {
	int n;
	vector<vector<int>> g, gt, tree, bucket, down;
	vector<int> S;
	vector<int> dsu, label, sdom, idom, id;
	int dfstime =0;

	DominatorTree(vector<vector<int>> & _g, int root) 
	  : n(sz(_g)), g(_g), gt(n), tree(n), bucket(n), down(n), 
	  S(n), dsu(n), label(n), sdom(n), idom(n), id(n) {
		prep(root); reverse(S.begin(), S.begin() + dfstime);
		for(int u : S) {
			for(int v : gt[u]) {
				int w = fnd(v);
				if(id[ sdom[w] ] < id[ sdom[u] ])
					sdom[u] = sdom[w];
			}
			gt[u].clear();
			if(u != root) bucket[ sdom[u] ].push_back(u);
			for(int v : bucket[u]) {
				int w = fnd(v);
				if(sdom[w] == sdom[v]) idom[v] = sdom[v];
				else idom[v] = w;
			}
			bucket[u].clear();
			for(int v : down[u]) dsu[v] = u;
			down[u].clear();
		}
		reverse(S.begin(), S.begin() + dfstime);
		for(int u : S) if(u != root) {
			if(idom[u] != sdom[u]) idom[u] = idom[ idom[u] ];
			tree[ idom[u] ].push_back(u);
		}
		idom[root] = root;
	}
	void prep(int u){
		S[dfstime] = u;
		id[u] = ++dfstime;
		label[u] = sdom[u] = dsu[u] = u;

		for(int v : g[u]){
			if(!id[v])
				prep(v), down[u].push_back(v);
			gt[v].push_back(u);
		}
	}

	int fnd(int u, int flag = 0){
		if(u == dsu[u]) return u;
		int v = fnd(dsu[u], 1), b = label[ dsu[u] ];
		if(id[ sdom[b] ] < id[ sdom[ label[u] ] ])
			label[u] = b;
		dsu[u] = v;
		return flag ? v : label[u];
	}

};
