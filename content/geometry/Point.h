/**
 * Author: Kactl, Arthur Botelho, Eduardo Freire
 * Description: 2D point structure
 * Status: not stress-tested
 */
constexpr float EPS=1e-12;
constexpr float PI=acos(-1);

bool eq(float a, float b) {
	return abs(a-b) < EPS;
}

template<class T>
struct Point {
	typedef Point P;
	static constexpr int ret[2][2] = {{3, 2}, {4, 1}};
	T x, y;

	Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return eq(x, p.x) and eq(y,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T operator*(P p) const { return x*p.x+y*p.y; }
	T operator^(P p) const { return x*p.y - y*p.x; }
	T dist2() const { return x*x + y*y; }
	int quad() const { return ret[x >= 0][y >= 0]; }

	// angle to x-axis in interval [0, 2*PI]
	double angle() const { 
		auto an=atan2(y,x);
		return an < 0 ? an+2*PI: an;
	}

	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; 
	}
	static bool angle_comp(P a, P b){
		int qa = a.quad(), qb = b.quad();
		return (qa == qb ? (a ^ b) > 0 : qa < qb);
	}
};

