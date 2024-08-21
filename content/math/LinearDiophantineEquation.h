/**
 * Author: Ruan Petrus
 * Description: Find a solution to equation a*x + b*y  = c
 * Time: O(log(a))
 * Status: not stress-tested
 */
array<ll, 3> exgcd(ll a, ll b) {
	if (a == 0) return {0, 1, b};
	auto [x, y, g] = exgcd(b % a, a);
	return {y - b / a * x , x, g};
}

// if (x,y) is a solution (x-kb/d, y+ka/d) for all integer k
array<ll, 4> find_any_solution(ll a, ll b, ll c) {
	assert(a != 0 || b != 0);
	auto[x, y, g] = exgcd(a, b);
	if (c % g) return {false, 0, 0, 0};
	x *= c / g;
	y *= c / g;
	return {true, x, y, g};
}
