/**
 * Author: Eduardo Freire
 * Description: Count primes less than or equal to floor(n/k) for every k.
 * Time: O(\frac{n^{3/4}}{\sqrt(\log(n))})
 * Memory: O(n)
*/

using ll = long long;
ll count_primes(ll n) {
    vector<ll> v;
    for (ll k = 1; k * k <= n; k++) {
        v.pb(n / k);
        v.pb(k);
    }
    sort(all(v));
    v.erase(unique(all(v)), v.end());

    ll sq = sqrt(n);
    auto geti = [&](ll x) -> int{
        if (x <= sq) return x - 1;
        else         return sz(v) - n / x;
    };

    auto dp = v;
    int a = 0;
    for (ll p = 2; p * p <= n; ++p) {
        if (dp[geti(p)] != dp[geti(p - 1)]) {
            a++;
            for (int i = sz(v) - 1; i >= 0; i--) {
                if (v[i] < p * p) break;
                dp[i] -= dp[geti(v[i] / p)] - a;
            }
        }
    }
    return dp[geti(n)] - 1;
}

