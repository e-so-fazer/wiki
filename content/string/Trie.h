/**
 * Author: Arthur Botelho
 * Description: Trie
 * Time: O(|S|) update and query
 * Memory: O(Sum of |S|)
 * Status: not tested
*/


template<class T>
struct Trie{
	vector<unordered_map<T, int>> g; vi cnt;
	Trie():g(1),cnt(1,0){}
	int new_node(){g.pb(unordered_map<T, int>()); cnt.pb(0); return sz(g)-1;}
	template<class S> void insert(const S & s){
		int cur = 0;
		for(T c : s){
			if (g[cur].count(c))cur = g[cur][c];
			else cur = g[cur][c] = new_node();
		}
		cnt[cur]++;
	}
};

struct alphabet{
	using T = char;
	static constexpr int sz = 26;
	static constexpr T inic = 'a';
};

template<class A>
struct Trie{
	using T = typename A::T;
	vector<vector<int>> g; vi cnt;
	Trie():g(1,vector<int>(A::sz,0)),cnt(1,0){}
	int new_node(){g.pb(vector<int>(A::sz,0)); cnt.pb(0); return sz(g)-1;}
	template<class S> void insert(const S & s){
		int cur = 0;
		for(T c : s){
			if (g[cur][c-A::inic])cur = g[cur][c-A::inic];
			else cur = g[cur][c-A::inic] = new_node();
		}
		cnt[cur]++;
	}
	template<class S> int count(const S & s){
		int cur = 0;
		for(T c : s){
			if (g[cur][c-A::inic])cur = g[cur][c-A::inic];
			else return 0;
		}
		return cnt[cur];
	}
};