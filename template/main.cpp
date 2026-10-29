// template code is uploaded to https://github.com/nanj0178/CP-Journey
// TLE:
//   - check1: due to O(MAX_V) initialization overhead on a large number of small test cases, instead of being linear to N.
// No Idea checklist:
//   - sequence to graph
#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
using namespace std;
// using namespace __gnu_pbds;
// template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define PRINTARRAY(st, en, a) for(int _i = st; _i <= en; _i++) {cout << a[_i] << (_i != en ? " " : "\n");}
#define PRINTARRAYALL(a) for(int _i = 0; _i < SZ(a); _i++) {cout << a[_i] << (_i != SZ(a) - 1 ? " " : "\n");}
#define SZ(A) (int)A.size()
#ifdef DEBUG
#define bug(...) cerr << '(', _printArg(#__VA_ARGS__), cerr << ") = ", _printValue(__VA_ARGS__)
#define bugarrall(...) cerr << '(', _printArg(#__VA_ARGS__), cerr << ") = ", _printArrAll(__VA_ARGS__)
template<typename T> void _printArg(T &&x) { cerr << x; }
template<typename T, typename ...S> void _printArg(T &&x, S&&...y) { cerr << x << ", "; _printArg(y...); }
template<typename T> void _printValue(T &&x) { cerr << x << endl; }
template<typename T, typename ...S> void _printValue(T &&x, S&&...y) { cerr << x << ", "; _printValue(y...); }
template<typename T> void _printArrAll(T &&x) { for(int _i = 0; _i < SZ(x); _i++) cerr << x[_i] << (_i != SZ(x) - 1 ? " " : "\n");}
#else
#define bug(...)
#define bugarrall(...)
#endif

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
using LL = long long;
const LL INF = 1e18;
const int MOD = 1000000007;
void solve() {
}
int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    // freopen("a.txt", "r", stdin);
    // freopen("a.txt", "w", stdout);    
    int testcase = 1;
    // cin >> testcase;
    while(testcase--) {
        solve();
    }
}

