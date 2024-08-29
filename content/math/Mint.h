/**
 * Author: Arthur Botelho
 * Description: modular int structure
 * Time: O(1) + and -, O(\log M) * and /
 * Memory: O(1)
 * Status: not stress-tested
*/

using ll = long long;
template<int M> struct Z{
	signed v;
	Z(int val=0){v = (val>=M ? (val%M) : val);}
	static Z<M> fexp(Z<M> a, int b){
		Z<M> res(1);
		for(;b;a=a*a,b>>=1)if(b&1)res=res*a;
		return res;
	}
	Z operator+(const Z<M> & o)const{
		signed a = v + o.v; 
		return Z<M>{a>=M?a-M:a};
	}
	Z operator-(const Z<M> & o)const{
		signed a = v - o.v;
		return Z<M>{a<0?a+M:a};
	}
	Z operator*(const Z<M> & o)const{
		return {((ll)v*o.v)%M};
	}
	Z operator/(const Z<M> & o)const{
		return (*this) * fexp(o, M-2);
	}
	bool operator==(const Z<M> & o)const{
		return v==o.v;
	}
	operator int()const{return v;}	
};

//using mint = Z<MOD> , where MOD is prime smaller than 2^32