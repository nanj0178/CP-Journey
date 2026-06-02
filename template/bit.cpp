#include <bits/stdc++.h>
using namespace std;
template <typename T>
struct BIT {
    int _n;
    vector<T> tree;

    BIT(int n) : _n(n), tree(n + 1, 0) {}
    // 1-based
    void add(int x, T v) {
        assert(x >= 1 && x <= _n);
        for(; x <= _n; x += x & -x) {
            tree[x] += v;
        }
    }

    T _query(int x) {
        assert(x <= _n);
        T s = 0;
        for(; x > 0; x -= x & -x) {
            s += tree[x];
        }
        return s;
    }
};