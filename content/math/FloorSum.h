/**
 * Author: Arthur Botelho
 * Description: floor sum
 * Time: O(\log (a+c))
 * Memory: O(1)
 * Status: stress-tested
*/

// Sum of floor(ax + b, c) for x in [0, n[

//a, c and n positive numbers, b non negative
template<class T> T floor_sum(T a, T b, T c, T n){
	if (n == 0)return 0;
	T ad = a/c, bd = b/c;
	a %= c; b %= c;
	T res = n * bd + (n * (n-1) / 2) * ad;
	T m = (a*n + b - a) / c;
	return res + m * (n-1) - floor_sum(c, c-b-1, a, m);
}