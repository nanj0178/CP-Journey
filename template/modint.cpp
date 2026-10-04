#include <bits/stdc++.h>
using namespace std;
using LL = long long;
int MOD = 998244353;

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

array<LL,3> extgcd(LL a, LL b) {
	// a * x1 + b * y1​ = g
	// b * x2 + (a % b) * y1​ = g
	// set a % b = a − a / b * b
	// => b * x2 + (a − a / b * b) * y2 = g
    // => b * x2 + a * y2 - a / b * b * y2 = g
	// => a * y2 + b (x2 - a / b * y2) = g
	// => x1 = y2
	// => y1 = (x2 - a / b * y2)
    if (b == 0) {
        return {a, 1, 0};
    }

    auto [g, x1, y1] = extgcd(b, a % b);

    LL x = y1;
    LL y = x1 - (a / b) * y1;

    return {g, x, y};
}