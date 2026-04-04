#include <bits/stdc++.h>
using namespace std;
using LL = long long;
/* 
rng settings:
// int
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int>(0, INT_MAX)(rng)
// long long
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<long long>(0, LONG_LONG_MAX)(rng);
*/
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const LL M = 991831889;
const LL C = uniform_int_distribution<LL>(0.1 * M, 0.9 * M)(rng);
const LL INF = 1e18;
const int MOD = 1000000007;
struct HashString {
    int n;
    vector<LL> pows, sums;

    HashString(string &s) : n(s.size()), pows(n + 1, 1), sums(n + 1, 0) {
        for (int i = 0; i < n; i++) {
            pows[i + 1] = pows[i] * C % M;
            sums[i + 1] = (sums[i] * C + s[i]) % M;
        }
    }

    /*
        quick recall
        len(s) = 3
        sum[r] = C^2 * s0 + C^1 * s1 + s2
        pow[i] = the shift length should be mul
        hash(1, 3) => want C^1 * s1 + s2 => sum[r] - sum[l] * shift len
    */
    // Returns the hash of the substring [l, r)
    // get hash of the string s, call hash(0, n)
    LL hash(int l, int r) {
        LL h = sums[r] - sums[l] * pows[r - l] % M;
        return (h % M + M) % M;
    }
};