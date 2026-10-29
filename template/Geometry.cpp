#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define F first
#define S second
#define X first
#define Y second
#define Point pair<long double, long double>
#define mp make_pair
const long double pi = acos(-1);

template<typename T>
pair<T, T> operator+(pair<T, T> a, pair<T, T> b){
    return mp(a.F + b.F, a.S + b.S);
}

template<typename T>
pair<T, T> operator-(pair<T, T> a, pair<T, T> b){
    return mp(a.F - b.F, a.S - b.S);
}

template<typename T>
pair<T, T> operator*(pair<T, T> a, T b){
    return mp(a.F * b, a.S * b);
}

template<typename T>
pair<T, T> operator/(pair<T, T> a, T b){
    return mp(a.F / b, a.S / b);
}

template<typename T>
T dot(pair<T, T> a, pair<T, T> b){
    return a.F * b.F + a.S * b.S;
}

template<typename T>
T cross(pair<T, T> a, pair<T, T> b){
    return a.F * b.S - a.S * b.F;
}

template<typename T>
T abs2(pair<T, T> a){
    return a.F * a.F + a.S * a.S;
}

template<typename T>
bool collinearity(pair<T, T> p1, pair<T, T> p2, pair<T, T> p3){
    return cross(p2 - p1, p3 - p1) == 0;
}

template<typename T>
bool inLine(pair<T, T> a, pair<T, T> b, pair<T, T> p){
    return collinearity(a, b, p) && dot(a - p, b - p) <= 0;
}

// rect check overlap
// (0,0) 到 (1,2)矩形可記為 (x, y, h, w) = (0, 0, 2, 3)
auto check = [](LL x1, LL y1, LL w1, LL h1, LL x2, LL y2, LL w2, LL h2) {
    LL xx1 = x1 + w1 - 1;
    LL yy1 = y1 + h1 - 1;
    LL xx2 = x2 + w2 - 1;
    LL yy2 = y2 + h2 - 1;
    if (min(xx1, xx2) < max(x1, x2) || min(yy1, yy2) < max(y1, y2)) {
        return false;
    }
    return true;
    // return (min(xx1, xx2) - max(x1, x2) + 1) * (min(yy1, yy2) - max(y1, y2) + 1); // 算size，沒驗證過
};

vector<Point> getConvexHull(vector<Point> &A) {
    sort(A.begin(), A.end());
    vector<Point> vex;
    for(int t = 0; t < 2; t++) {
        int base = vex.size();
        for(auto p : A) {
            while(vex.size() - base >= 2) {
                Point last2 = vex[vex.size() - 2]; 
                Point last1 = vex[vex.size() - 1];
                if (cross(last1 -  last2, p - last2) < 0) {
                    vex.pop_back();
                } else {
                    break;
                }
            }
            vex.push_back(p);
        }
        vex.pop_back();
        reverse(A.begin(), A.end());
    }
    return vex;
}
// Sort points by polar angle and use cross instead of atan2l
/*
    auto half = [&] (Point x) {
        // 0 is up, 1 is down.
        return (x.Y < 0) || (x.Y == 0 && x.X < 0);
    };
    auto cmp = [&](Point a, Point b) {
        int ha = half(a);
        int hb = half(b);
        if (ha != hb) return ha < hb;
        LL c = cross(a, b);
        if (c != 0) return c > 0;
        return abs2(a) < abs2(b);
    };
*/