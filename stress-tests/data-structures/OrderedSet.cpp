
/*
   Used in the following problems:
   - https://cses.fi/problemset/task/1076
*/

#include "../utilities/template.h"
#include "../../content/data-structures/OrderedSet.h"

int main() {
	set<int> s; multiset<int> ms;
	ordered_set<int> o; ordered_multiset<int> mo;
	int n = 10;
	rep(i, 0, 2*n){
		s.insert(i%n); ms.insert(i%n);
		o.insert(i%n); mo.insert(i%n);
	}
	assert(sz(s)==sz(o) and sz(ms)==sz(mo));
	rep(i, 0, n/2){
		s.erase(i); ms.erase(ms.find(i));
		o.erase(i); mo.erase(i);
	}
	assert(sz(s)==sz(o) and sz(ms)==sz(mo));
	rep(i, -n, n-1){
		assert(*s.lower_bound(i) == *o.lower_bound(i));
		assert(*ms.lower_bound(i) == *mo.lower_bound(i));
		assert(*s.upper_bound(i) == *o.upper_bound(i));
		assert(*ms.upper_bound(i) == *mo.upper_bound(i));
	}
	vi vs, vms;
	for(int x : s)vs.pb(x);
	for(int x : ms)vms.pb(x);
	rep(i, 0, n){
		int anss = lower_bound(all(vs), i) - vs.begin();
		int ansms = lower_bound(all(vms), i) - vms.begin();
		assert(anss == o.order_of_key(i));
		assert(ansms == mo.order_of_key(i));
	}
	rep(i, 0, sz(vs))assert(vs[i] == *o.find_by_order(i));
	rep(i,0 , sz(vms))assert(vms[i] == *mo.find_by_order(i));
	cout << "Test passed!\n";
}
