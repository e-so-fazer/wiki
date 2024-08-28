/**
 * Author: Eduardo Freire
 * Description: Centroid decomposition
 * Time: O(log(V) * subproblem)
 * Memory: O(V)
 * Status: not yet tested
  */

struct Centroid {
	vector<vi> g;
	int rt, n;
	vi rmv, ssz, par;

	Centroid(vector<vi> ag, int art) : g(ag), rt(art), n(g.size()), rmv(n,0), ssz(n,0), par(n,0) {
		centroid_tree(art);
	} 
	 
	int sizes(int a, int p=-1) {
		int ans=1;
		for(auto& b:g[a]) {
			if (b == p or rmv[b]) continue;
			ans+=sizes(b,a);
		}
		return ssz[a]=ans;
	}
	 
	void calcdists(int a, int d, int p, vi& dists) {
		dists[d]++;
		for(auto& b : g[a]) {
			if (rmv[b] or b==p) continue;
			calcdists(b, d+1, a,dists);
		}
	}	
 
	int centroid(int a, int tsize, int p=-1) {
		for(auto& b:g[a]) {
			if (rmv[b] or b==p) continue;
			if (ssz[b] * 2 > tsize) return centroid(b,tsize, a);
		}
		return a;
	}
	void centroid_tree(int a, int p=-1) {
		int c=centroid(a, sizes(a));
	 
		rmv[c]=true;
		par[c]=p;
	 
		solvesub(c); 
	 
		for(auto& b : g[c]) {
			if (rmv[b]) continue;
			centroid_tree(b, c);
		}
	}

	// do not visit removed guys (if rmv[b] continue)
	void solvesub(int a) {

	}
};

