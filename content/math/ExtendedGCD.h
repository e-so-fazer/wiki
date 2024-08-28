/**
 * Author: Eduardo Freire
 * Description: Returns integers (d,x,y) such that ax + by = d and d=gcd(a,b)
 * Time: O(log(min(a,b)))
 * Status: not stress-tested
 */

tuple<int,int,int> egcd(int a, int b) {
	int ar=a, as=1,s=0,at=0,t=1;
	for (int r=b; r;) {
		int q = ar / r;
		tie(ar, r) = pii(r,ar-q*r);
		tie(as, s) = pii(s,as-q*s);
		tie(at, t) = pii(t,at-q*t);
	}
	return {ar, as, at};
}

