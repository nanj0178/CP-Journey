#include <bits/stdc++.h>
using namespace std;
struct DSU {
    vector<int> par;
    vector<int> groupSize;
    int getParent(int x) {
        if (par[x] == x) {
            return x;
        }
        return par[x] = getParent(par[x]);
    }
    int getSize(int x) {
        int px = getParent(x);
        return groupSize[px];
    }
    void merge(int x, int y) {
        int px = getParent(x);
        int py = getParent(y);
        if (px == py) {
            return;
        }
        if (groupSize[px] > groupSize[py]) {
            swap(px, py);
        }
        par[px] = py;
        groupSize[py] += groupSize[px];
    }
    void init(int n) {
        par.assign(n, 0);
        iota(par.begin(), par.end(), 0);
        groupSize.assign(n, 1);
    }
    DSU() {
    }
    DSU(int n) {
        init(n);
    }
};