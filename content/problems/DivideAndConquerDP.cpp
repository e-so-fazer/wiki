/**
 * Author: Ruan Petrus
 * Description: Partition and array of size N in K groups, the cost of each group is the sum of $(freq[x] * x)^2$ 
   for each element inside the group. Divide and conquer DP
 * Time: O(K * N * \log N)
 * Status: stress-tested
 */

struct Info {
	vector<int> freq;
	ll sum = 0;
};

void solve() {
	int n, k;
	cin >> n >> k;
	vector<int> as(n);
	rep(i, 0, n) cin >> as[i];

	vector<ll> dp_before(n);
	vector<ll> dp_curr(n);

	vector<int> currf(n+1);

	// You can consider this are the ranges
	// [minj ... maxj] info((maxj, l), [l ... r]
	// Info should contain compressed information between maxj and l exclusive
	auto dc = [&](auto rec, int l, int r, int minj, int maxj, Info & info) {
		if (l > r) return;
		int mid = l + (r-l)/2;

		ll sum = info.sum;
		pair<ll, int> best(oo, -1);

		auto add_epilogue = [&](int j) { // Add j from range [mid ... (maxj, or l))
			ll a = as[j];
			ll f = currf[a] + info.freq[a];
			sum -= a*a * f*f;
			currf[a]++;
			f = currf[a] + info.freq[a];
			sum += a*a * f*f;
		};
		auto add_ans = [&](int j) { // Add j where j is a possible ans [maxj ... minj]
			add_epilogue(j);
			ll res = sum + (j ? dp_before[j-1] : 0);
			chmin(best, {res, j});
		};
		auto clear_global =[&](int j) { // Clear global variable, if in use
			int a = as[j];
			currf[a] = 0;
		};

		for (int j = mid; j >= max(l, maxj+1); j--) add_epilogue(j);
		for (int j = min(maxj, mid); j >= minj; j--) add_ans(j);

		for (int j = minj; j <= min(maxj, mid); j++) clear_global(j);
		for (int j = max(l, maxj+1); j <= mid; j++) clear_global(j);

		dp_curr[mid] = best.first; // Calc ans

		int bestj = best.second;
		assert(bestj != -1);

		auto add_info = [&](int j) { // Add j information to info
			ll a = as[j];
			ll f = info.freq[a];
			info.sum -= a*a * f*f;
			info.freq[a]++;
			f = info.freq[a];
			info.sum += a*a * f*f;
		};
		auto rollback_info = [&](int j) { // Rollback info for before j information
			ll a = as[j];
			ll f = info.freq[a];
			info.sum -= a*a * f*f;
			info.freq[a]--;
			f = info.freq[a];
			info.sum += a*a * f*f;
		};

		for (int j = bestj+1; j <= min(maxj, l-1); j++) add_info(j);
			rec(rec, l, mid - 1, minj, bestj, info); // Calling left side
		for (int j = min(maxj, l-1); j >= bestj+1; j--) rollback_info(j);

		for (int j = max(l, maxj+1); j <= mid; j++) add_info(j);
			rec(rec, mid+1, r, bestj, maxj, info); // Calling right side
		for (int j = mid; j >= max(l, maxj+1); j--) rollback_info(j);
	};

	Info info;
	info.freq = vector<int>(n+1, 0);

	fill(all(dp_before), oo);
	rep(i, 0, k) {
		dc(dc, 0, n-1, 0, n-1, info);
		dp_before.swap(dp_curr);
	}
	cout << dp_before[n-1] << endl;
}
