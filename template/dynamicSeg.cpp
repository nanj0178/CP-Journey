#include <bits/stdc++.h>
using namespace std;
using LL = long long;
struct Data
{
    int cnt;
    array<LL,2> sum;
    Data defaultVal() {
        return {0, {0,0}};
    }
    void add(LL v) {
        cnt++;
        sum[cnt % 2] += v;
    }
    Data merge(const Data& x, const Data& y) {
        if (x.cnt % 2 == 0) {
            return {x.cnt + y.cnt, {x.sum[0] + y.sum[0], x.sum[1] + y.sum[1]}};
        }
        return {x.cnt + y.cnt, {x.sum[0] + y.sum[1], x.sum[1] + y.sum[0]}};
    }    
}; 
// careful: lnode / rnode's default value is zero
// node 0 value is a special case for empty node
int root = 1;
const int MAXN = 3e5 * 32;
int lNode[MAXN] = {}, rNode[MAXN] = {};
Data valNode[MAXN] = {};
int totalNode = 1;
Data query(int L, int R, int id, int l, int r) {
    if (id == 0) return Data().defaultVal();
    if (l <= L && R <= r) return valNode[id];
    int mid = L + (R - L) / 2;
    if (r <= mid) return query(L, mid, lNode[id], l, r);
    if (mid <= l) return query(mid, R, rNode[id], l, r);
    return Data().merge(query(L, mid, lNode[id], l, r), query(mid, R, rNode[id], l, r));
}
void update(int L, int R, int &id, int p, LL v) {
    if (id == 0) id = ++totalNode;
    if (R - L == 1) {
        valNode[id].add(v);
        return;
    }
    int mid = L + (R - L) / 2;
    if (p < mid) update(L, mid, lNode[id], p, v);
    if (mid <= p) update(mid, R, rNode[id], p, v);
    valNode[id] = Data().merge(valNode[lNode[id]], valNode[rNode[id]]);
}

