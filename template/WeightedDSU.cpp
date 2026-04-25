#include <bits/stdc++.h>
using namespace std;
// 0-based
struct WeightedDSU {
    vector<int> par;
    vector<int> groupSize;
    vector<int> releation;
    vector<array<int,2>> color_cnt; // change it to what question wants
    int getParent(int x) {
        if (par[x] == x) {
            return x;
        }
        int root = getParent(par[x]);
        releation[x] ^= releation[par[x]]; 
        return par[x] = root;        
    }    
    array<int, 2> val(int x) {
        int px = getParent(x);
        return color_cnt[px];
    }
    bool merge(int x, int y, int v) {
        int px = getParent(x);
        int py = getParent(y);
        if (px == py) {
            if (releation[x] ^ releation[y] != v) return false;
            return true;
        }
        if (groupSize[px] > groupSize[py]) {
            swap(px, py);
            swap(x, y);
        }
        par[px] = py;
        groupSize[py] += groupSize[px];
        releation[py] = releation[x] ^ v ^ releation[y];
        if (v == 0) {
            color_cnt[py][0] += color_cnt[px][0];
            color_cnt[py][1] += color_cnt[px][1];
        } else {
            color_cnt[py][0] += color_cnt[px][1];
            color_cnt[py][1] += color_cnt[px][0];
        }        
        return true;
    }
    void init(int n) {
        par.assign(n, 0);
        iota(par.begin(), par.end(), 0); // assign 0,1,2,3,4,5...
        groupSize.assign(n, 1);
        releation.assign(n, 0);
        color_cnt.assign(n, {1, 0});        
    }
};