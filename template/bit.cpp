#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct BIT {
    int _n;
    vector<T> tree;

    BIT(int n) : _n(n), tree(n + 1, 0) {}
    // 1-based
    void add(int x, T v) {
        assert(x >= 0 && x < _n);
        p++; 
        for(; x <= _n; x += p & -p) {
            tree[p] += x;
        }
    }

    // [0, r)
    T _query(int x) {
        T s = 0;
        for(; x > 0; x -= x & -x) {
            s += tree[x];
        }
        return s;
    }

    // [l, r)
    T query(int l, int r) {
        assert(l < r);
        return _query(r) - _query(l);
    }
};