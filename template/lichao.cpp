
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
const LL INF = 4e18;
struct Line
{
    bool hasValue;
    LL a, b;
    Line() {
        hasValue = false;
        a = b = 0;
    }
    Line(bool has, LL _a, LL _b) {
        hasValue = has;
        a = _a;
        b = _b;
    }    
    bool isBigger(Line &l, LL x) {
        LL lv = l.a * x + l.b;
        LL selfv = a * x + b;
        return selfv >= lv;
    }    
    LL f(LL x) {
        return a * x + b;
    }
}; 
// careful: lnode / rnode value is zero
// node 0 value is empty node value
const int MAXN = 2e5 * 32;
int lNode[MAXN] = {}, rNode[MAXN] = {};
Line valNode[MAXN] = {};
int totalNode = 0;
LL query(LL L, LL R, int id, LL x) {
    if (valNode[id].hasValue == false) return -INF;
    LL mid = L + (R - L) / 2;
    LL curV = valNode[id].f(x);
    LL childv = -INF;
    if (x < mid) {
        childv = query(L, mid, lNode[id], x);
    } else {
        childv = query(mid, R, rNode[id], x);
    }
    return max(childv, curV);
}
bool isLeft(Line &v1, Line &v2, LL L) {
    return v2.f(L) > v1.f(L);
}
void update(LL L, LL R, int &id, Line &v) {
    if (id == 0) id = ++totalNode;
    LL mid = L + (R - L) / 2;
    if (valNode[id].hasValue == false) {
        valNode[id] = v;
        return;
    }
    if (!valNode[id].isBigger(v, mid)) {
        swap(valNode[id], v);
    }
    if (R - L == 1) return;
    if (isLeft(valNode[id], v, L)) {
        update(L, mid, lNode[id], v);
    } else {
        update(mid, R, rNode[id], v);
    }
}