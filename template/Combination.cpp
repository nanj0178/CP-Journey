#include <bits/stdc++.h>
using namespace std;
using LL = long long;
const int MOD = 998244353;
struct mi {
	int v;
	explicit operator int() const { return v; }
	mi() { v = 0; }
	mi(long long _v) : v(_v % MOD) { v += (v < 0) * MOD; }
};
mi &operator+=(mi &a, mi b) {
    long long sum = (long long)a.v + b.v;
    if (sum >= MOD) sum -= MOD;
    a.v = sum;
    return a;
}
mi &operator-=(mi &a, mi b) {
	if ((a.v -= b.v) < 0) a.v += MOD;
	return a;
}
mi operator+(mi a, mi b) { return a += b; }
mi operator-(mi a, mi b) { return a -= b; }
mi operator*(mi a, mi b) { return mi((long long)a.v * b.v); }
mi &operator*=(mi &a, mi b) { return a = a * b; }
mi pow(mi a, long long p) {
	assert(p >= 0);
	return p == 0 ? 1 : pow(a * a, p / 2) * (p & 1 ? a : 1);
}
mi inv(mi a) {
	assert(a.v != 0);
	return pow(a, MOD - 2);
}
mi operator/(mi a, mi b) { return a * inv(b); }
struct Combination {
    int _n;
    vector<mi> fac, inv_fac;
    Combination(int size) {
        _n = size;
        fac.assign(size + 1, 0);
        inv_fac.assign(size + 1, 0);
        build();
    }
    
    mi C(int n, int a) {
        if (n < 0 || a < 0 || n - a < 0) return 0;
        assert(n <= _n && a <= _n);
        return fac[n] * inv_fac[a] * inv_fac[n - a];
    }
    mi C2(LL n, int a) {
        if (n < 0 || a < 0 || n - a < 0) return 0;
        mi res = 1;
        for(LL i = n, j = 1; j <= a; i--, j++) {
            res *= mi(i);
            res = res / mi(j);
        }
        return res;
    }    
    void build() {
        fac[0] = 1;
        for(int i = 1; i <= _n; i++) {
            fac[i] = i * fac[i - 1];
        }
        inv_fac[_n] = inv(fac[_n]);
        for(int i = _n - 1; i >= 0; i--) {
            inv_fac[i] = inv_fac[i + 1] * (i + 1);
        }
    }
};