/**
 * Author: Arthur Botelho
 * Description: Z function
 * Time: O(N)
 * Memory: O(N)
 * Status: stress-tested
*/

template<class S>
vi zfunction(S& s){
	int n = sz(s); vi z(n, 0);
	for(int l=0,r=0,i=1;i<n;i++){
		for(int& j=z[i]=(i<=r)*min(r-i+1,z[i-l]);i+j<n and s[j]==s[i+j];j++);
		if (i+z[i]-1>r)r=i+z[i]-1,l=i;
	}
	z[0] = n; return z;
}