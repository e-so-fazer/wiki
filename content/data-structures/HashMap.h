/**
 * Author: Arthur Botelho
 * Description: Safe and fast unordered map
 * Requires Monoid (op, id)
 * Time: O(~1)
 * Memory: O(N)
 * Status: stress-tested
 */

struct custom_hash{
	using T = uint64_t;	
	static T splitmix64(T x){
		x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(T x)const{ //if keys are not T type, conversion is necessary
    	static const T r = chrono::steady_clock::now().time_since_epoch().count();
    	return splitmix64(x+r);
    }
};
template<class A, class B>
using hash_map = unordered_map<A, B, custom_hash>;

#include<bits/extc++.h>
#define GNU __gnu_pbds
template<class A, class B>
using hash_table = GNU::gp_hash_table<A, B, custom_hash, equal_to<A>,
GNU::direct_mask_range_hashing<>, GNU::linear_probe_fn<>, 
GNU::hash_standard_resize_policy<GNU::hash_exponential_size_policy<>, 
GNU::hash_load_check_resize_trigger<>, true>>;