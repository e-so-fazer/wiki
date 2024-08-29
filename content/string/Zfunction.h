/**
 * Author: Arthur Botelho
 * Description: Z function
 * Time: O(N)
 * Memory: O(N)
 * Status: not stress-tested
*/

vi zfunction(string& s){
	int n = sz(s);
	vi z(n, 0);
	int l=0, r=0;
	rep(i, 1, n){
		int j = (i<=r)*min(r-i+1,z[i-l]);
		while(j < n and s[j]==s[i+j])j++;
		if (i+j-1 > r)r=i+j-1,l=i;
		z[i] = j;
	}
	z[0] = n; return z;
}