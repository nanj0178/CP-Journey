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

