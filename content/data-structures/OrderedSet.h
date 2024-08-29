/**
 * Author: Arthur Botelho
 * Description: ordered/indexed set and multiset
 * Bad constant factor, works only in Linux
 * Time: O(\log N) operations
 * Memory: O(N)
 * Status: stress-tested
*/

#include<bits/extc++.h> //include it before int long long
#define GNU __gnu_pbds
template<class T, class B = GNU::null_type>
using ordered_set = GNU::tree<T, B, less<T>, GNU::rb_tree_tag, 
GNU::tree_order_statistics_node_update>;

template<class T>
struct ordered_multiset{
	ordered_set<pair<T, int>> o; int c;
	ordered_multiset():c(0){}
	const int order_of_key(T x){return o.order_of_key({x, -1});}
	const T* find_by_order(int p){return &(*o.find_by_order(p)).first;}
	void insert(T x){o.insert({x, c++});}
	void erase(T x){o.erase(o.lower_bound({x, 0}));} //only one element by call
	const unsigned size(){return o.size();}
	const T* lower_bound(T x){return &(*o.lower_bound({x, 0})).first;}
	const T* upper_bound(T x){return &(*o.upper_bound({x, c})).first;}
};
  
void example(){
	ordered_set<int> o1;
	ordered_multiset<int> o2;
	rep(i, 0, 3){
		o1.insert(i); o2.insert(i); o2.insert(i);
	}
	cout << o1.size() << ' ' << o2.size() << endl; //3 6
	int p1 = o1.order_of_key(1); //=1, one element smaller than 1
	int p2 = o2.order_of_key(2); //=2
	int x = *o1.find_by_order(2); //=2
	int y = *o2.find_by_order(2); //=1
	cout << x << ' ' << y << endl;
}