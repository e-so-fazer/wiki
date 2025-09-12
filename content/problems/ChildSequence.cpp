/**
 * Author: Arthur Botelho
 * Description: child and sequence 
 * Time: O(nlogn)
 * Status: oot tested
 */

/*
Operations: 1 l r: range sum
l r x: a[i] %= x for i in [l, r]
k x: a[k] = x
*/
#include<bits/stdc++.h>
using namespace std;  
//basic types:
#define int long long
#define float long double
//methods:
#define pb push_back
#define eb emplace_back
#define ppb pop_back
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
//loops:
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define repinv(i, a, b) for(int i = (a); i >= (b); i--)
//input/output:
template<class T> T read(){T a; cin >> a; return a;}
#define esp ' '
#define endl '\n'
#define debug(var) cout << #var << ": " << var << endl
template<class T> ostream& operator<<(ostream& os, vector<T> v){
	if (v.empty()) return os << "";
	rep(i, 0, sz(v)-1)os << v[i] << esp;
	return os << v.back();
}
//using and typedef:
typedef vector<int> vi;
typedef pair<int, int> pii;
//constants:
constexpr int oo = (((unsigned int)-1)>>3);
constexpr int MOD = 998244353;

/*Rascunho
*/
/*Ideias
*/


#define CLZ __builtin_clz
template<class S>
struct SegBeats{ using T = typename S::T; using L = typename S::L;
	int n; vector<T> seg; vector<L> lz; vector<bool> ig;
	int ceillog(signed x){return CLZ(1)-CLZ(x)+(__builtin_popcount(x)!=1);}
	SegBeats(int s):n(1<<ceillog(s)),seg(2*n,S::id),lz(2*n),ig(2*n,1){}
	void update(L v, int l, int r){return updt(v,l,r,1,0,n-1);}
	T query(int l, int r){return qry(l,r,1,0,n-1);}
	void updt(L v, int lq, int rq, int no, int lx, int rx){
		//debug((vi{v,lq,rq,no,lx,rx}));
		if (rq < lx or rx < lq or S::brk(v,seg[no]))return;
		if (lq <= lx and rx <= rq and S::tag(v,seg[no],rx-lx+1)){
			apply(no, v, rx-lx+1); return;
		}
		prop(no,lx,rx); int mid = lx+(rx-lx)/2;
		updt(v,lq,rq,no<<1,lx,mid);
		updt(v,lq,rq,no<<1|1,mid+1,rx);
		seg[no] = S::op(seg[no<<1],seg[no<<1|1]);
	}
	T qry(int lq, int rq, int no, int lx, int rx){
		prop(no,lx,rx); int mid = lx+(rx-lx)/2;
		if (rq < lx or rx < lq)return S::id;
		if (lq <= lx and rx <= rq)return seg[no];
		return S::op(qry(lq,rq,no<<1,lx,mid),qry(lq,rq,no<<1|1,mid+1,rx));
	}
	inline void apply(int p, L v, int s){
		seg[p] = S::ch(seg[p],v,s);
	}
	void prop(int p, int l, int r){
		if (l==r)return;
		//apply(p<<1, seg[p].max1, (r-l+1)/2);
		//apply(p<<1|1, seg[p].max1, (r-l+1)/2);
	}
};

struct node{
	int mx;
	int sum;
};

struct Spec{ using T = node; using L = pii;
	static constexpr T id = node{-oo, 0};
	static T op(T a, T b){
		node n;
		n = node{max(a.mx, b.mx), a.sum+b.sum};
		return n;
	}
	static T ch(T a, L b, int s){
		if (b.first == 0){
			a.mx %= b.second;
			a.sum = a.mx;
		}
		else{
			a.mx = a.sum = b.second;
		}
		return a;
	}
			
	static L cmp(L a, L b){return b;}
	static bool brk(L a, T b){
		return (a.first==0 and b.mx < a.second);
	}
	static bool tag(L a, T b, int s){
		return s==1;
	}
};

void solvetestcase(){
    int n, q; cin >> n >> q;
    SegBeats<Spec> seg(n);
    rep(i, 0, n)seg.update({1, read<int>()}, i, i);
    while(q--){
    	int t; cin >> t;
    	if (t==1){
    		int l, r; cin >> l >> r; l--; r--;
    		cout << seg.query(l, r).sum << endl;
    	}
    	if (t==2){
    		int l, r, x; cin >> l >> r >> x; l--; r--;
    		seg.update({0, x}, l, r);
    	}
    	if (t==3){
    		int p, x; cin >> p >> x; p--;
    		seg.update({1, x}, p, p);
    	}
    }
}

signed main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t=1;
	//cin>>t;
	rep(i,0,t)solvetestcase();
}