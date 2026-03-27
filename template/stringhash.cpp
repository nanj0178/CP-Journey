#include <bits/stdc++.h>
using namespace std;
using LL = long long;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const LL M = 991831889;
const LL C = uniform_int_distribution<LL>(0.1 * M, 0.9 * M)(rng);
const LL INF = 1e18;
const int MOD = 1000000007;
struct HashString {
    int n;
    vector<LL> pows, sums;

    HashString(string &s) : n(s.size()), pows(n + 1, 1), sums(n + 1) {
        for (int i = 1; i <= n; i++) {
            pows[i] = pows[i - 1] * C % M;
            sums[i] = (sums[i - 1] * C + s[i - 1]) % M;
        }
    }

    // Returns the hash of the substring [l, r)
    // get hash of the string s, call hash(0, n)
    LL hash(int l, int r) {
        LL h = sums[r] - sums[l] * pows[r - l];
        return (h % M + M) % M;
    }
};