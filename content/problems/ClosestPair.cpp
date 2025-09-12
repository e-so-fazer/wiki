/**
 * Author: Arthur Botelho
 * Description: closest pair of points in Euclidean distance
 * Time: O(nlogn)
 * Status: oot tested
 */

int dist(point a, point b){
	point c = a-b; return c.x * c.x + c.y * c.y; //euclidean distance
}

point rev(point a){
	return point(a.y, a.x);
}

pair<point, point> mindist(vector<point> ps){
	sort(all(ps)); assert ps.size() > 1;
	set<point> revs; revs.insert(rev(ps[0])); revs.insert(rev(ps[1]));
	int ans = dist(ps[0], ps[1]);
	pair<point, point> closest = {ps[0], ps[1]};
	int l=0, n=ps.size();
	rep(r, 2, n){
		int d = ceil(sqrt(ans));
		while(l<n and ps[l].x+d < ps[r].x){
			revs.erase(rev(ps[l])); l++;
		}
		point comp = rev(ps[r]);
		comp.x -= d; comp.y -= d;
		auto beg = revs.lower_bound(comp);
		comp.x += 2*d;
		auto end = revs.lower_bound(comp);
		while(beg != end){
			int curd = dist(ps[r], rev(*beg));
			if (curd < ans){
				ans = curd; closest = {ps[r], rev(*beg)};
			}
			beg++;
		}
		revs.insert(rev(ps[r]));
	}
	return closest; //or return ans;
}