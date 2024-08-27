/**
 * Author: Kactl
 * Description: Polynomial multiplication modulo 998244353
 * Time: O(n log(n))
 * Status: not stress-tested
 */

constexpr int MOD=998244353;

int fpow(int a, int b) {
	int x=1;
	while(b) {
		if (b&1) x=(ll)x*a%MOD;

		a=(ll)a*a%MOD;
		b/=2;
	}
	return x;
}

void fft(vi &a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vi rt(2, 1);
	for (static int k = 2, s = 2; k < n; k *= 2, s++) {
		rt.resize(n);
		ll z[] = {1, fpow(62, MOD >> s)};
		rep(i,k,2*k) rt[i] = (ll) rt[i / 2] * z[i & 1] % MOD;
	}
	vi rev(n);
	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
			ll z = (ll) rt[j + k] * a[i + j + k] % MOD; int &ai = a[i + j];
			a[i + j + k] = ai - z + (z > ai ? MOD : 0);
			ai += (ai + z >= MOD ? z - MOD : z);
		}
}
vi mul(vi &a, vi &b) {
	if (a.empty() || b.empty()) return {};
	int s = sz(a) + sz(b) - 1,
	    n = 1 << (32-__builtin_clz(s));
	ll inv = fpow(n, MOD - 2);
	vi l(a), r(b), out(n);
	l.resize(n), r.resize(n);
	fft(l), fft(r);
	rep(i,0,n)
		out[-i & (n - 1)] = (ll)l[i] * r[i] % MOD * inv % MOD;
	fft(out);
	return {out.begin(), out.begin() + s};
}

