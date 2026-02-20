/**
 * Author: Arthur Botelho
 * Description: Merge Sort Tree
 * Time: O(\log^2 N)
 * Memory: O(N \log N)
 * Status: not tested
 */

template<class T>
struct MGST{
	int n, h; vector<vector<T>> t;
	int lg(int x){return __builtin_clz(1)-__builtin_clz(x);}
	MGST(vector<T> v): n(sz(v)), h(lg(n)){
		if (n != (1<<h))n = 1<<(++h);
		t.assign(h, vector<T>(n));
		rep(i,0,sz(v))t[0][i] = v[i];
		rep(i,sz(v),n)t[0][i] = oo; //non-existent
		rep(k,0,h)for(int i = 0, s = 1<<k; i < n; i += 2*s){
			int p1=0, p2=0;
			rep(p,i,i+2*s){
				if (p1==s)t[k+1][p] = t[k][i+s+p2], p2++;
				else if (p2==s)t[k+1][p] = t[k][i+p1], p1++;
				else if (t[k][i+p1] < t[k][i+s+p2])t[k+1][p] = t[k][i+p1], p1++;
				else t[k+1][p] = t[k][i+s+p2], p2++;
			}
		}
	}
	T query_helper(T x, int k, int l){
		auto it = upper_bound(t[k]+l, t[k]+l+(1<<k), x);
		if (it == t[k]+l)return 0;
		else return *prev(it);
	}
	 
	T lb(int x, int l, int r){ //biggest <= x in [l, r]
		T ans = 0; r++;
		for(int k = 0; l < r; k++){
			if ((l>>k)&1){
				ans = max(ans, query_helper(x, k, l));
				l += 1<<h;
			}
			if ((r>>k)&1){
				r -= 1<<k;
				ans = max(ans, query_helper(x, k, l));
			}
		}
		return ans;
	}
};

